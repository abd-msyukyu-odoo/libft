/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:26:10 by dabeloos          #+#    #+#             */
/*   Updated: 2019/06/17 18:26:12 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			ft_btree_initialize_leaf(t_bnode *leaf, t_bnode *parent,
	t_memitem *memitem)
{
	leaf->named = NULL;
	leaf->left = NULL;
	leaf->right = NULL;
	leaf->rank = 0;
	leaf->up = parent;
	leaf->memitem = memitem;
}

int					ft_btree_construct_extmem(t_btree *btree,
	t_memanager *bnode_mmng)
{
	if (!btree || !bnode_mmng)
		return (-1);
	ft_memused_initialize(&btree->mused);
	btree->root = (t_bnode*)ft_memanager_get(bnode_mmng, &btree->mused);
	if (!btree->root)
		return (0);
	ft_btree_initialize_leaf(btree->root, NULL, btree->mused.last);
	btree->cmp = ft_strcmp;
	btree->mmng = bnode_mmng;
	return (1);
}

void				ft_btree_free_extmem(t_btree *btree)
{
	ft_memanager_refill(btree->mmng, &btree->mused);
}

static int			ft_btree_construct_leaf(t_btree *btree, t_bnode *old_leaf,
	t_bnode **leaf)
{
	*leaf = ft_memanager_get(btree->mmng, &btree->mused);
	if (!*leaf)
		return (0);
	ft_btree_initialize_leaf(*leaf, old_leaf, btree->mused.last);
	return (1);
}

static int			ft_btree_construct_leaves(t_btree *btree, t_bnode *old_leaf)
{
	if (!ft_btree_construct_leaf(btree, old_leaf, &old_leaf->left) ||
		!ft_btree_construct_leaf(btree, old_leaf, &old_leaf->right))
		return (0);
	return (1);
}

static t_bnode		*ft_btree_get_bnode(t_btree *btree, char *key)
{
	t_bnode			*cur;
	int				cmpr;

	ft_printf("searching for %s\n\n", key);
	cur = btree->root;
	while (cur->rank && (cmpr = btree->cmp(key, cur->named->key)))
	{
		ft_printf("key : %s\n", cur->named->key);
		ft_printf("rank : %d\n", cur->rank);
		t_bnode *tmp;
		tmp = cur;
		if (cmpr < 0)
		{
			cur = cur->left;
			ft_printf("left\n\n");
		}
		else
		{
			cur = cur->right;
			ft_printf("right\n\n");
		}
		//
		if (cur->right == tmp || cur->left == tmp)
		{
			ft_printf("key : %s\n", cur->named->key);
			ft_printf("rank : %d\n", cur->rank);
			ft_printf("error loop");
			exit(-1);
		}
	}
	return (cur);
}

t_named				*ft_btree_get(t_btree *btree, char *key)
{
	t_bnode			*target;

	if (!btree || !key)
		return (NULL);
	target = ft_btree_get_bnode(btree, key);
	return ((!target->rank) ? NULL : target->named);
}

int					ft_btree_contains(t_btree *btree, char *key)
{
	return (ft_btree_get_bnode(btree, key) != NULL);
}

static int			ft_bnode_has_two_leaves(t_bnode *bnode)
{
	if (!bnode->left || !bnode->right)
		return (0);
	return (!bnode->left->rank && !bnode->right->rank);
}

static t_bnode		**ft_btree_bnode_referent(t_btree *btree, t_bnode *bnode)
{
	if (btree->root == bnode)
		return (&btree->root);
	if (bnode->up->right == bnode)
		return (&bnode->up->right);
	return (&bnode->up->left);
}

static int			ft_bnode_sibling_spin(t_bnode *child, t_bnode **sibling)
{
	if (child->up->left == child)
	{
		*sibling = child->up->right;
		return (1);
	}
	*sibling = child->up->left;
	return (-1);
}

static void			ft_btree_rotate(t_btree *btree, t_bnode *bn, int spin)
{
	t_bnode			*up;
	t_bnode			**referent;

	up = bn->up;
	referent = ft_btree_bnode_referent(btree, up);
	if (up == btree->root)
		ft_printf("switching root\n");
	*referent = bn;
	bn->up = up->up;
	up->up = bn;
	if (spin == 1)
	{
		up->left = bn->right;
		bn->right->up = up;
		bn->right = up;
	}
	else
	{
		up->right = bn->left;
		bn->left->up = up;
		bn->left = up;
	}
	up->rank--;
	return ;
}

static void			ft_btree_rebalance_added(t_btree *btree, t_bnode *bn)
{
	t_bnode			*sib;
	int				spin;

	while (bn->up && bn->up->rank == bn->rank)
	{
		spin = ft_bnode_sibling_spin(bn, &sib);
		if (bn->rank == bn->up->rank && bn->rank > sib->rank + 1)
		{
			if (((bn->left->rank - bn->right->rank) ^ spin) < 0)
			{
				ft_printf("double rotation\n");
				sib = (spin == 1) ? bn->right : bn->left;
				sib->rank++;
				ft_btree_rotate(btree, sib, -1 * spin);
				ft_btree_rotate(btree, sib, spin);
			}
			else
			{
				ft_printf("simple rotation\n");
				ft_btree_rotate(btree, bn, spin);
			}
			return ;
		}
		bn->up->rank++;
		bn = bn->up;
	}
}

static void			ft_btree_rebalance_deleted_double_rotate(t_btree *btree,
	t_bnode *bn, t_bnode *sib, int spin)
{
	bn->up->rank--;
	bn = (spin == 1) ? sib->left : sib->right;
	bn->rank++;
	ft_btree_rotate(btree, bn, spin);
	ft_btree_rotate(btree, bn, -1 * spin);
	bn->rank++;
}

static void			ft_btree_rebalance_deleted_single_rotate(t_btree *btree,
	t_bnode *bn, t_bnode *sib, int spin)
{
	bn = bn->up;
	sib->up->rank++;
	ft_btree_rotate(btree, sib->up, -1 * spin);
	if (ft_bnode_has_two_leaves(bn))
		bn->rank = 1;
}

static int			ft_btree_rebalance_deleted_to_leaf(t_btree *btree, t_bnode *remain)
{
	t_bnode			*bn;

	if (!remain->rank && btree->root != remain)
	{
		ft_bnode_sibling_spin(remain, &bn);
		if (!bn->rank)
		{
			ft_printf("demote leaf : previous : %d\n", remain->up->rank);
			remain->up->rank = 1;
			return (1);
		}
	}
	return (0);
}

static void			ft_btree_rebalance_deleted(t_btree *btree, t_bnode *bn)
{
	t_bnode			*sib;
	int				spin;

	if (ft_btree_rebalance_deleted_to_leaf(btree, bn))
		bn = bn->up;
	while (bn->up && bn->up->rank - bn->rank >= 3)
	{
		ft_printf("trigger detection : %d | up : %d\n", bn->rank, bn->up->rank);
		if (bn->up->rank - bn->rank > 3)
		{
			ft_printf("error : rank diff : %d = %d - %d\n",
				bn->up->rank - bn->rank,
				bn->up->rank,
				bn->rank);
			exit(-1);
		}
		spin = ft_bnode_sibling_spin(bn, &sib);
		if (sib->rank - bn->rank == 2)
		{
			if (sib->left->rank - sib->right->rank == spin)
			{
				ft_printf("double rotation\n");
				ft_btree_rebalance_deleted_double_rotate(btree, bn, sib, spin);
				return ;
			}
			sib = (spin == 1) ? sib->right : sib->left;
			if (sib->up->rank - sib->rank == 1)
			{
				ft_printf("simple rotation\n");
				ft_btree_rebalance_deleted_single_rotate(btree, bn, sib, spin);
				return ;
			}
			ft_printf("second demote\n");
			sib->up->rank--;
		}
		ft_printf("first demote\n");
		bn->up->rank--;
		bn = bn->up;
	}
}

int					ft_btree_add(t_btree *btree, t_named *item)
{
	t_bnode			*target;

	if (!btree || !item || !item->key)
		return (-1);
	target = ft_btree_get_bnode(btree, item->key);
	if (target->rank)
		return (-2);
	if (!ft_btree_construct_leaves(btree, target))
		return (0);
	target->named = item;
	target->rank = 1;
	ft_btree_rebalance_added(btree, target);
	return (1);
}

t_named				*ft_btree_replace(t_btree *btree, t_named *item)
{
	t_bnode			*target;
	t_named			*out;

	if (!btree || !item || !item->key)
		return (NULL);
	target = ft_btree_get_bnode(btree, item->key);
	if (!target->rank)
		return (NULL);
	out = target->named;
	target->named = item;
	return (out);
}

static int			ft_btree_cut_leaf(t_btree *btree, t_bnode *cut,
	t_bnode **remain)
{
	t_bnode			*dead_leaf;

	if (!cut->left->rank)
	{
		dead_leaf = cut->left;
		*remain = cut->right;
	}
	else if (!cut->right->rank)
	{
		dead_leaf = cut->right;
		*remain = cut->left;
	}
	else
		return (0);
	ft_memused_recover(&btree->mused, dead_leaf->memitem);
	return (1);
}

static int			ft_btree_cut_branch(t_btree *btree, t_bnode *cut)
{
	t_bnode			**referent;
	t_bnode			*remain;

	if (!ft_btree_cut_leaf(btree, cut, &remain))
		return (0);
	referent = ft_btree_bnode_referent(btree, cut);
	remain->up = cut->up;
	*referent = remain;
	t_bnode			*sib;
	if (btree->root != remain)
	{
		ft_bnode_sibling_spin(remain, &sib);
		ft_printf("rank deleted : %d | remain : %d | sibling : %d | up : %d\n",
			cut->rank, remain->rank, sib->rank, remain->up->rank);
	}
	ft_btree_rebalance_deleted(btree, remain);
	return (1);
}

static t_bnode		*ft_btree_get_min_bnode(t_bnode *bnode)
{
	while (bnode->left->rank)
		bnode = bnode->left;
	return (bnode);
}

static t_bnode		*ft_btree_remove_bnode(t_btree *btree, char *key)
{
	t_bnode			*target;
	t_bnode			*swapper;
	t_named			*named;

	target = ft_btree_get_bnode(btree, key);
	if (target->rank)
	{
		if (ft_btree_cut_branch(btree, target))
			return (target);
		swapper = ft_btree_get_min_bnode(target->right);
		named = target->named;
		target->named = swapper->named;
		swapper->named = named;
		target = swapper;
		ft_btree_cut_branch(btree, target);
	}
	return ((target->rank) ? target : NULL);
}

t_named				*ft_btree_remove(t_btree *btree, char *key)
{
	t_bnode			*target;
	t_named			*out;

	if (!btree || !key)
		return (NULL);
	target = ft_btree_remove_bnode(btree, key);
	if (target)
	{
		out = target->named;
		ft_memused_recover(&btree->mused, target->memitem);
	}
	else
		out = NULL;
	return (out);
}

static int			ft_btree_add_typecast(void *receiver, void *sent)
{
	return (ft_btree_add((t_btree*)receiver, (t_named*)sent));
}

static int			ft_array_add_typecast(void *receiver, void *sent)
{
	return (ft_array_add((t_array*)receiver, (t_named*)sent));
}

int					ft_btree_bnode_iteration(void *receiver, t_bnode *sent,
	int (*f)(void *receiver, void *sent))
{
	int				out;

	out = (sent->rank) ? 1 : 0;
	if (out > 0 && sent->left->rank)
		out = ft_btree_bnode_iteration(receiver, sent->left, f);
	if (out > 0)
		out = f(receiver, sent->named);
	if (out > 0 && sent->right->rank)
		out = ft_btree_bnode_iteration(receiver, sent->right, f);
	return (out);
}

int					ft_btree_fill_copy(t_btree *old, t_btree *new)
{
	return (ft_btree_bnode_iteration(new, old->root, ft_btree_add_typecast));
}

int					ft_btree_fill_array(t_btree *btree, t_array *array)
{
	return (ft_btree_bnode_iteration(array, btree->root,
		ft_array_add_typecast));
}
