/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mbtree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:24:04 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 16:24:05 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			ft_mbtree_initialize_leaf(t_bnode *leaf, t_bnode *parent)
{
	leaf->named = NULL;
	leaf->left = NULL;
	leaf->right = NULL;
	leaf->rank = 0;
	leaf->up = (t_bnode*)parent;
}

int					ft_mbtree_construct(t_mbtree *mbtree,
	t_memanager *mmng, int (*cmp)(void *s1, void *s2))
{
	if (!mbtree || !mmng)
		return (-1);
	mbtree->btree.root = (t_bnode*)ft_typemanager_get(tbnode_tmng,
		&tbtree->tused);
	if (!tbtree->btree.root)
		return (0);
	ft_tbtree_initialize_leaf((t_tbnode*)tbtree->btree.root, NULL,
		tbtree->tused.last);
	tbtree->btree.cmp = cmp;
	tbtree->tmng = tbnode_tmng;
	return (1);
}