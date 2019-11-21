/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 18:41:14 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 18:41:14 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_mbtree_initialize_leaf(t_bnode *leaf, t_bnode *parent)
{
	leaf->named = NULL;
	leaf->left = NULL;
	leaf->right = NULL;
	leaf->rank = 0;
	leaf->up = (t_bnode*)parent;
}

int					ft_mbtree_initialize(t_mbtree *mbtree, t_memanager *mmng,
	int (*cmp)(void *s1, void *s2))
{
	if (!mbtree)
		return (0);
	mbtree->btree.root = (t_bnode*)ft_memanager_get(mmng, sizeof(t_bnode));
	if (!mbtree->btree.root)
		return (0);
	ft_mbtree_initialize_leaf(mbtree->btree.root, NULL);
	mbtree->btree.cmp = cmp;
	mbtree->mmng = mmng;
	return (1);
}
