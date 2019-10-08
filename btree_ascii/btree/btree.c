/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 14:06:35 by dabeloos          #+#    #+#             */
/*   Updated: 2019/10/04 14:06:36 by dabeloos         ###   ########.fr       */
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
	t_memanager *bnode_mmng, int (*cmp)(void *s1, void *s2))
{
	if (!btree || !bnode_mmng)
		return (-1);
	ft_memused_initialize(&btree->mused);
	btree->root = (t_bnode*)ft_memanager_get(bnode_mmng, &btree->mused);
	if (!btree->root)
		return (0);
	ft_btree_initialize_leaf(btree->root, NULL, btree->mused.last);
	btree->cmp = cmp;
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

int					ft_btree_construct_leaves(t_btree *btree, t_bnode *old_leaf)
{
	if (!ft_btree_construct_leaf(btree, old_leaf, &old_leaf->left) ||
		!ft_btree_construct_leaf(btree, old_leaf, &old_leaf->right))
		return (0);
	return (1);
}
