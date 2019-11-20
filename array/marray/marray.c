/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 19:28:14 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 19:28:15 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_marray			*ft_marray_construct(t_memanager *mmng, size_t size, 
	size_t sizeof_item)
{
	t_marray			*out;

	if (!mmng || !(out = (t_array*)ft_memanager_get(mmng, sizeof(t_marray))))
		return (NULL);
	if (size > 0 && sizeof_item > 0)
	{
		out->array.items = ft_memanager_get(mmng, size * sizeof_item);
		out->array.size = size;
		out->array.sizeof_item = sizeof_item;
	}
	else
	{
		out->array.items = ft_memanager_get(mmng, sizeof(void*));
		out->array.size = 1;
		out->array.sizeof_item = sizeof(void*);
	}
	if (!out->array.items)
	{
		ft_memanager_refill(mmng, out);
		return (NULL);
	}
	out->array.n_items = 0;
	out->mmng = mmng;
	return (out);
}

void				ft_marray_free(t_marray *marray)
{
	if (!marray)
		return ;
	ft_memanager_refill(marray->mmng, marray->array.items);
	ft_memanager_refill(marray->mmng, marray);
}
