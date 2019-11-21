/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:43:02 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 21:43:03 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_mbtree			*ft_mhmap_get(t_mhmap *mhmap, void *item)
{
	return ((t_mbtree*)ft_array_get(mhmap->hmap.array,
		mhmap->hmap.hash(item, mhmap->hmap.array->size)));
}

int					ft_mhmap_contains(t_mhmap *mhmap, void *item)
{
	t_btree		*btree;

	btree = (t_btree*)ft_mhmap_get(mhmap, item);
	return ((btree->root) ? ft_btree_contains(btree, item) : 0);
}
