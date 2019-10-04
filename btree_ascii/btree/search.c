/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 15:47:43 by dabeloos          #+#    #+#             */
/*   Updated: 2019/10/04 15:47:44 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bnode				*ft_btree_get_bnode(t_btree *btree, char *key)
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

t_bnode				*ft_btree_get_min_bnode(t_bnode *bnode)
{
	while (bnode->left->rank)
		bnode = bnode->left;
	return (bnode);
}
