/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shrink.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 16:19:24 by dabeloos          #+#    #+#             */
/*   Updated: 2019/10/04 16:19:30 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	ft_btree_rebalance_deleted(btree, remain);
	return (1);
}

static t_bnode		*ft_btree_remove_bnode(t_btree *btree, void *key)
{
	t_bnode			*target;
	t_bnode			*swapper;
	void			*named;

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

void				*ft_btree_remove(t_btree *btree, void *key)
{
	t_bnode			*target;
	void			*out;

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
