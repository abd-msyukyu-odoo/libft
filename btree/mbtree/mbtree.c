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

t_mbtree			*ft_mbtree_construct(t_memanager *mmng,
	int (*cmp)(void *s1, void *s2))
{
	t_mbtree		*mbtree;

	if (!mmng)
		return (NULL);
	mbtree = (t_mbtree*)ft_memanager_get(mmng, sizeof(t_mbtree));
	if (!mbtree)
		return (NULL);
	mbtree->btree.root = (t_bnode*)ft_memanager_get(mmng, sizeof(t_bnode));
	if (!mbtree->btree.root)
		return (NULL);
	ft_mbtree_initialize_leaf(mbtree->btree.root, NULL);
	mbtree->btree.cmp = cmp;
	mbtree->mmng = mmng;
	return (mbtree);
}

static void			ft_mbtree_free_iteration(t_memanager *mmng, t_bnode *bnode)
{
	if (bnode->rank)
	{
		ft_mbtree_free_iteration(mmng, bnode->left);
		ft_mbtree_free_iteration(mmng, bnode->right);
	}
	ft_memanager_refill(mmng, bnode);
}

void				ft_mbtree_free(t_mbtree *mbtree)
{
	if (!mbtree)
		return ;
	ft_mbtree_free_iteration(mbtree->mmng, mbtree->btree.root);
	ft_memanager_refill(mbtree->mmng, mbtree);
}

static int			ft_mbtree_construct_leaf(t_mbtree *mbtree,
	t_bnode *old_leaf, t_bnode **leaf)
{
	*leaf = ft_memanager_get(mbtree->mmng, sizeof(t_bnode));
	if (!*leaf)
		return (0);
	ft_mbtree_initialize_leaf(*leaf, old_leaf);
	return (1);
}

int					ft_mbtree_construct_leaves(t_mbtree *mbtree,
	t_bnode *old_leaf)
{
	if (!ft_mbtree_construct_leaf(mbtree, old_leaf, &old_leaf->left) ||
		!ft_mbtree_construct_leaf(mbtree, old_leaf, &old_leaf->right))
		return (0);
	return (1);
}
