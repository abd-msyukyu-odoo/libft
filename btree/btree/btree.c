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
	t_typeitem *typeitem)
{
	leaf->named = NULL;
	leaf->left = NULL;
	leaf->right = NULL;
	leaf->rank = 0;
	leaf->up = parent;
	leaf->typeitem = typeitem;
}

int					ft_btree_construct_extmem(t_btree *btree,
	t_typemanager *bnode_tmng, int (*cmp)(void *s1, void *s2))
{
	if (!btree || !bnode_tmng)
		return (-1);
	ft_typeused_initialize(&btree->tused);
	btree->root = (t_bnode*)ft_typemanager_get(bnode_tmng, &btree->tused);
	if (!btree->root)
		return (0);
	ft_btree_initialize_leaf(btree->root, NULL, btree->tused.last);
	btree->cmp = cmp;
	btree->tmng = bnode_tmng;
	return (1);
}

void				ft_btree_free_extmem(t_btree *btree)
{
	ft_typemanager_refill(btree->tmng, &btree->tused);
}

static int			ft_btree_construct_leaf(t_btree *btree, t_bnode *old_leaf,
	t_bnode **leaf)
{
	*leaf = ft_typemanager_get(btree->tmng, &btree->tused);
	if (!*leaf)
		return (0);
	ft_btree_initialize_leaf(*leaf, old_leaf, btree->tused.last);
	return (1);
}

int					ft_btree_construct_leaves(t_btree *btree, t_bnode *old_leaf)
{
	if (!ft_btree_construct_leaf(btree, old_leaf, &old_leaf->left) ||
		!ft_btree_construct_leaf(btree, old_leaf, &old_leaf->right))
		return (0);
	return (1);
}
