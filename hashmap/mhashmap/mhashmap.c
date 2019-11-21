/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mhashmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:18:38 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 21:18:40 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_mhmap				*ft_mhmap_construct(t_memanager *mmng, size_t size,
	size_t (*hash)(void *s, size_t size))
{
	t_mhmap			*mhmap;

	if (!mmng)
		return (NULL);
	mhmap = (t_mhmap*)ft_memanager_get(mmng, sizeof(t_mhmap));
	if (!mhmap)
		return (NULL);
	mhmap->hmap.array = (t_array*)ft_marray_construct(mmng, size,
		sizeof(t_mbtree));
	if (!mhmap->hmap.array)
		return (NULL);
	ft_bzero(mhmap->hmap.array->items, size * sizeof(t_mbtree));
	mhmap->hmap.array->n_items = size;
	mhmap->mmng = mmng;
	mhmap->hmap.hash = hash;
	return (mhmap);
}

void				ft_mhmap_free(t_mhmap *mhmap)
{
	size_t			i;
	t_mbtree		*mbtree;

	if (!mhmap)
		return ;
	i = 0;
	while (i < mhmap->hmap.array->size)
	{
		mbtree = (t_mbtree*)ft_array_get(mhmap->hmap.array, i);
		ft_mbtree_free(mbtree);
	}
	ft_marray_free((t_marray*)mhmap->hmap.array);
	ft_memanager_refill(mhmap->mmng, mhmap);
}
