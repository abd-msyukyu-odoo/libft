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

	cur = btree->root;
	while (cur->rank && (cmpr = btree->cmp(key, cur->named->key)))
	{
		if (cmpr < 0)
			cur = cur->left;
		else
			cur = cur->right;
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

	up = bn->up;
	bn->up = up->up;
	up->up = bn;
	if (btree->root == up)
		btree->root = bn;
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
			if (bn->left->rank - bn->right->rank != spin)
			{
				sib = (spin == 1) ? bn->right : bn->left;
				sib->rank++;
				ft_btree_rotate(btree, sib, -1 * spin);
				ft_btree_rotate(btree, sib, spin);
			}
			else
				ft_btree_rotate(btree, bn, spin);
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
}

static void			ft_btree_rebalance_deleted_single_rotate(t_btree *btree,
	t_bnode *bn, t_bnode *sib, int spin)
{
	bn = bn->up;
	sib->up->rank++;
	ft_btree_rotate(btree, sib->up, -1 * spin);
	if (ft_bnode_has_two_leaves(bn))
		bn->rank--;
}

static void			ft_btree_rebalance_deleted(t_btree *btree, t_bnode *bn)
{
	t_bnode			*sib;
	int				spin;

	while (bn->up && bn->up->rank - bn->rank == 3)
	{
		spin = ft_bnode_sibling_spin(bn, &sib);
		if (sib->rank - bn->rank == 2)
		{
			if (sib->left->rank - sib->right->rank == spin)
			{
				ft_btree_rebalance_deleted_double_rotate(btree, bn, sib, spin);
				return ;
			}
			sib = (spin == 1) ? sib->right : sib->left;
			if (sib->up->rank - sib->rank == 1)
			{
				ft_btree_rebalance_deleted_single_rotate(btree, bn, sib, spin);
				return ;
			}
			sib->up->rank--;
		}
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

static t_bnode		**ft_btree_bnode_referent(t_btree *btree, t_bnode *bnode)
{
	if (btree->root == bnode)
		return (&btree->root);
	if (bnode->up->right == bnode)
		return (&bnode->up->right);
	return (&bnode->up->left);
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

	target = ft_btree_get_bnode(btree, key);
	if (target)
	{
		if (ft_btree_cut_branch(btree, target))
			return (target);
		swapper = ft_btree_get_min_bnode(target->right);
		target->named = swapper->named;
		target = swapper;
		ft_btree_cut_branch(btree, target);
	}
	return (target);
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

	out = f(receiver, sent->named);
	if (out > 0 && sent->left->rank)
		out = ft_btree_bnode_iteration(receiver, sent->left, f);
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
