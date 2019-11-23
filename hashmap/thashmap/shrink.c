/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shrink.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:43:07 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 21:43:08 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_thmap_remove(t_thmap *thmap, void *item)
{
	t_tbtree		*tbtree;

	if (!thmap || !item)
		return (-1);
	tbtree = (t_tbtree*)ft_hmap_get((t_hmap*)thmap, item);
	if (!tbtree->tmng)
		return (0);
	if (ft_tbtree_remove(tbtree, item))
	{
		if (!tbtree->btree.root->rank)
		{
			ft_tbtree_refill(tbtree);
			tbtree->tmng = NULL;
		}
		return (1);
	}
	else
		return (0);
	return ((ft_tbtree_remove(tbtree, item)) ? 1 : 0);
}
