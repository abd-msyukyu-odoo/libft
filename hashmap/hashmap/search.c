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

t_btree				*ft_hmap_get(t_hmap *hmap, void *item)
{
	return ((t_btree*)ft_array_get(hmap->array,
		hmap->hash(item, hmap->array->size)));
}

int					ft_hmap_contains(t_hmap *hmap, void *item)
{
	t_btree		*btree;

	if (!hmap || !item)
		return (-1);
	btree = (t_btree*)ft_hmap_get(hmap, item);
	return ((btree->root) ? ft_btree_contains(btree, item) : 0);
}
