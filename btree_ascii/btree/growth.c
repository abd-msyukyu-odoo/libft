/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   growth.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 16:05:10 by dabeloos          #+#    #+#             */
/*   Updated: 2019/10/04 16:05:11 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

int					ft_btree_add(t_btree *btree, void *item)
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
