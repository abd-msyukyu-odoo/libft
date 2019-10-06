/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memarray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:35:44 by dabeloos          #+#    #+#             */
/*   Updated: 2019/09/27 16:35:45 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_manager/memanager2.h"
#include "libft.h"

static void					ft_memarray_configure_items(t_memarray *memarray)
{
	t_memjump				*first;
	t_memjump				*last;

	memarray->memory->n_items = memarray->memory->size;
	first = (t_memjump*)ft_array_get(memarray->memory, 0);
	last = (t_memjump*)ft_array_get(memarray->memory, memarray->memory->size
		- sizeof(t_memjump));
	ft_memjump_initialize(first, NULL, last);

	t_memitem				*memitem;

	while (index < memarray->array->size)
	{
		memitem = (t_memitem*)ft_array_inject(memarray->memitems);
		memitem->item = ft_array_inject(memarray->array);
		memitem->next = prev;
		memitem->i_memarray = i_memarray;
		memitem->n_used = 0;
		memitem->next_oldest = NULL;
		memitem->next_recovery = NULL;
		prev = memitem;
		++index;
	}
	memarray->unused = prev;
	memarray->n_unused = index;
}

void						ft_memarray_free(t_memarray *memarray)
{
	if (!memarray)
		return ;
	ft_array_free(memarray->memory);
	free(memarray);
}

static t_memarray			*ft_memarray_error(t_memarray *memarray)
{
	ft_memarray_free(memarray);
	return (NULL);
}

size_t						ft_memarray_minimal_size(void)
{
	return (sizeof(t_memcache) + 2 * sizeof(t_memjump));
}

t_memarray					*ft_memarray_construct(size_t size)
{
	t_memarray				*out;

	out = (t_memarray*)malloc(sizeof(t_memarray));
	if (!out)
		return (NULL);
	out->memory = ft_array_construct(size / sizeof(char), sizeof(char));
	if (!out->memory)
		return (ft_memarray_error(out));
	ft_memarray_configure_items(out);
	return (out);
}