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
		return (0);
	ft_memused_initialize(&btree->mused);
	btree->root = (t_bnode*)ft_memanager_get(bnode_mmng, &btree->mused);
	if (!btree->root)
		return (0);
	ft_btree_initialize_leaf(btree->root, NULL, btree->mused.last);
	btree->cmp = ft_strcmp;
	btree->mmng = bnode_mmng;
	return (1);
}

static int			ft_btree_construct_leaf(t_btree *btree, t_bnode *old_leaf,
	t_bnode **leaf)
{
	*leaf = ft_memanager_get(btree->mmng, &btree->mused);
	if (*leaf)
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
	return ((!target) ? NULL : target->named);
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

static void			ft_btree_rebalance(t_btree *btree, t_bnode *bn)
{
	t_bnode			*sib;
	int				spin;

	while (bn->up)
	{
		if (bn->up->rank > bn->rank)
			return ;
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

int					ft_btree_add(t_btree *btree, t_named *item)
{
	t_bnode			*cur;

	if (!btree || !item || !item->key)
		return (-1);
	cur = ft_btree_get_bnode(btree, item->key);
	if (cur->rank)
		return (-2);
	if (!ft_btree_construct_leaves(btree, cur))
		return (0);
	cur->named = item;
	cur->rank = 1;
	ft_btree_rebalance(btree, cur);
	return (1);
}

