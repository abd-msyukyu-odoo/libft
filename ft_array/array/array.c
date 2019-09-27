/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:26:10 by dabeloos          #+#    #+#             */
/*   Updated: 2019/06/17 18:26:12 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

t_array				*ft_array_construct(unsigned int size, size_t
	sizeof_item)
{
	t_array			*out;

	out = (t_array*)malloc(sizeof(t_array));
	if (!out)
		return (NULL);
	if (size > 0 && sizeof_item > 0)
	{
		out->items = malloc(size * sizeof_item);
		out->size = size;
		out->sizeof_item = sizeof_item;
	}
	else
	{
		out->items = malloc(sizeof(void*));
		out->size = 1;
		out->sizeof_item = sizeof(void*);
	}
	if (!out->items)
	{
		free(out);
		return (NULL);
	}
	out->n_items = 0;
	return (out);
}

void				ft_array_free(t_array *array)
{
	if (!array)
		return ;
	free(array->items);
	free(array);
}

int					ft_array_extend_size(t_array *array, unsigned int new_size)
{
	void			*items;

	if (new_size <= array->size)
		return (0);
	if (!(items = malloc(new_size * array->sizeof_item)))
		return (0);
	ft_memmove(items, array->items, array->sizeof_item * array->n_items);
	free(array->items);
	array->items = items;
	array->size = new_size;
	return (1);
}

int					ft_array_extend_size_skip(t_array *array,
	unsigned int new_size, unsigned int skip_from)
{
	void			*items;

	if (new_size <= array->size || skip_from >= array->n_items)
		return (0);
	if (!(items = malloc(new_size * array->sizeof_item)))
		return (0);
	ft_memmove(items, array->items, array->sizeof_item * skip_from);
	ft_memmove(&items[(skip_from + 1) * array->sizeof_item],
		&array->items[skip_from * array->sizeof_item],
		array->sizeof_item * (array->n_items - skip_from));
	free(array->items);
	array->items = items;
	array->n_items++;
	array->size = new_size;
	return (1);
}

int					ft_array_add(t_array *array, void *item)
{
	if (!item)
		return (-1);
	if (array->n_items >= array->size && !ft_array_extend_size(array,
		2 * array->size))
		return (0);
	ft_memmove(&array->items[array->n_items * array->sizeof_item], item,
		array->sizeof_item);
	array->n_items++;
	return (1);
}

int					ft_array_insert(t_array *array, unsigned int index,
	void *item)
{
	unsigned int	i;

	if (index > array->n_items)
		return (0);
	if (!item)
		return (-1);
	if (index == array->n_items)
		return (ft_array_add(array, item));
	i = array->n_items;
	if (array->n_items >= array->size && !ft_array_extend_size_skip(array,
		2 * array->size, index))
		return (0);
	else
		while (i-- > index)
			ft_memmove(&array->items[(i + 1) * array->sizeof_item],
				&array->items[i * array->sizeof_item], array->sizeof_item);
	ft_memmove(&array->items[index * array->sizeof_item], item,
		array->sizeof_item);
	array->n_items++;
	return (1);
}

int					ft_array_remove(t_array *array, unsigned int index,
	void *removed)
{
	if (index >= array->n_items)
		return (0);
	if (removed)
		ft_memmove(removed, &array->items[index * array->sizeof_item],
			array->sizeof_item);
	while (++index < array->n_items)
		ft_memmove(&array->items[(index - 1) * array->sizeof_item],
			&array->items[index * array->sizeof_item], array->sizeof_item);
	if (array->n_items > 0)
		array->n_items = array->n_items - 1;
	return (1);
}

unsigned int		ft_array_index(t_array *array, void *item)
{
	unsigned int	i;

	if (item == NULL)
		return (array->n_items);
	i = 0;
	while (i < array->n_items)
	{
		if (!ft_memcmp(&array->items[i * array->sizeof_item], item,
			array->sizeof_item))
			return (i);
		i++;
	}
	return (i);
}

int					ft_array_contains(t_array *array, void *item)
{
	return (ft_array_index(array, item) != array->n_items);
}

int					ft_array_remove_first(t_array *array, void *item)
{
	unsigned int	i;

	i = ft_array_index(array, item);
	return (ft_array_remove(array, i, NULL) != 0);
}

void				*ft_array_get(t_array *array, unsigned int index)
{
	if (index >= array->n_items)
		return (NULL);
	return (&array->items[index * array->sizeof_item]);
}

void				*ft_array_inject(t_array *array)
{
	if (array->n_items >= array->size && !ft_array_extend_size(array,
		2 * array->size))
		return (NULL);
	array->n_items++;
	return (ft_array_get(array, array->n_items - 1));
}