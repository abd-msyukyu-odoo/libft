/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_requests.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:35:50 by dabeloos          #+#    #+#             */
/*   Updated: 2019/09/27 16:35:51 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int							ft_memanager_refill(t_memanager *memanager,
	t_memused *used)
{
	t_memarray				*memarray;
	t_memitem				*tmp;

	if (!used || !used->oldest || !used->memitem)
		return (0);
	while (used->oldest)
	{
		memarray = *(t_memarray**)ft_array_get(memanager->memarrays,
			used->oldest->i_memarray);
		if (!memarray)
			return (0);
		tmp = used->oldest->next;
		used->oldest->next = memarray->unused;
		memarray->unused = used->memitem;
		memarray->n_unused += used->memitem->n_used;
		if (used->memitem->i_memarray < memanager->i_available)
			memanager->i_available = used->memitem->i_memarray;
		used->memitem = tmp;
		used->oldest = used->oldest->next_oldest;
		if (!used->memitem && used->oldest)
			return (0);
	}
	return (1);
}

static void					*ft_memanager_get_same_memarray(t_memused *used,
	t_memarray *memarray)
{
	t_memitem			*old;

	old = used->memitem;
	if (!used->oldest)
		used->oldest = memarray->unused;
	used->memitem = memarray->unused;
	memarray->unused = memarray->unused->next;
	memarray->n_unused--;
	used->memitem->next = old;
	used->memitem->n_used = (!old) ? 1 : old->n_used + 1;
	return (used->memitem->item);
}

static void					*ft_memanager_get_other_memarray(t_memused *used,
	t_memarray *memarray)
{
	memarray->unused->next_oldest = used->oldest;
	used->oldest = memarray->unused;
	memarray->unused = memarray->unused->next;
	memarray->n_unused--;
	used->oldest->next = used->memitem;
	used->memitem = used->oldest;
	used->memitem->n_used = 1;
	return (used->memitem->item);
}

void						*ft_memanager_get(t_memanager *memanager,
	t_memused *used)
{
	t_memarray			*memarray;

	memarray = *(t_memarray**)ft_array_get(memanager->memarrays,
		memanager->i_available);
	while (!memarray->n_unused)
	{
		if (memanager->i_available == memanager->memarrays->n_items - 1 &&
			!ft_memanager_extend_size(memanager, memarray->array->size))
			return (NULL);
		memanager->i_available++;
		memarray = *(t_memarray**)ft_array_get(memanager->memarrays,
			memanager->i_available);
	}
	if (!used->memitem || used->memitem->i_memarray == memanager->i_available)
		return (ft_memanager_get_same_memarray(used, memarray));
	else
		return (ft_memanager_get_other_memarray(used, memarray));
}
