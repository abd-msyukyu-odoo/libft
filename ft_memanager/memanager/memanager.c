#include "memanager.h"

void						ft_memarray_free(t_memarray *memarray)
{
	if (!memarray)
		return ;
	ft_array_free(memarray->array);
	ft_array_free(memarray->memitems);
	free(memarray);
}

static t_memarray			*ft_memarray_error(t_memarray *memarray)
{
	ft_memarray_free(memarray);
	return (NULL);
}

void						ft_memanager_free(t_memanager *memanager)
{
	unsigned int			i;

	if (!memanager)
		return ;
	if (memanager->memarrays)
	{
		i = 0;
		while (i < memanager->memarrays->n_items)
		{
			ft_memarray_free(
				*(t_memarray**)ft_array_get(memanager->memarrays, i));
			++i;
		}
		ft_array_free(memanager->memarrays);
	}
	free(memanager);
	return ;
}

static t_memanager			*ft_memanager_error(t_memanager *memanager)
{
	ft_memanager_free(memanager);
	return (NULL);
}

/*
** take all item pointer from array to fill [memitems] and put the last memitem
** in [unused]
*/
static void					ft_memarray_configure_items(t_memarray *memarray, 
	unsigned int index, t_memitem *prev, unsigned int i_memarray)
{
	t_memitem				*memitem;

	while (index < memarray->array->size)
	{
		memitem = (t_memitem*)ft_array_inject(memarray->memitems);
		memitem->item = ft_array_inject(memarray->array);
		memitem->next = prev;
		memitem->i_memarray = i_memarray;
		memitem->n_used = 0;
		memitem->next_newest = NULL;
		memitem->next_oldest = NULL;
		prev = memitem;
		++index;
	}
	memarray->unused = prev;
	memarray->n_unused = index;
}

t_memarray					*ft_memarray_construct(unsigned int size,
	size_t sizeof_item, unsigned int memindex)
{
	t_memarray				*out;

	out = (t_memarray*)malloc(sizeof(t_memarray));
	if (!out)
		return (NULL);
	out->array = ft_array_construct(size, sizeof_item);
	out->memitems = ft_array_construct(size, sizeof(t_memitem));
	if (!out->array || !out->memitems)
		return (ft_memarray_error(out));
	ft_memarray_configure_items(out, 0, NULL, memindex);
	return (out);
}

t_memanager					*ft_memanager_construct(unsigned int size,
	size_t sizeof_item)
{
	t_memanager				*out;
	t_memarray				**injector;

	out = (t_memanager*)malloc(sizeof(t_memanager));
	if (!out || !(out->memarrays = ft_array_construct(1, sizeof(t_memarray*)))
		|| !(injector = (t_memarray**)ft_array_inject(out->memarrays))
		|| !(*injector = ft_memarray_construct(size, sizeof_item, 0)))
		return (ft_memanager_error(out));
	out->i_available = 0;
	return (out);
}

int							ft_memanager_extend_size(t_memanager *memanager,
	unsigned int new_size)
{
	t_memarray				**injector;

	injector = (t_memarray**)ft_array_inject(memanager->memarrays);
	if (!injector || !(*injector = ft_memarray_construct(new_size,
		(*(t_memarray**)ft_array_get(memanager->memarrays,
			0))->array->sizeof_item,
		memanager->memarrays->n_items - 1)))
		return (0);
	return (1);
}

int							ft_memanager_refill(t_memanager *memanager,
	t_memused *used)
{
	t_memarray				*memarray;

	if (!used || !used->oldest || !used->memitem)
		return (0);
	while (used->oldest)
	{
		memarray = *(t_memarray**)ft_array_get(memanager->memarrays,
			used->oldest->i_memarray);
		if (!memarray)
			return (0);
		used->oldest->next = memarray->unused;
		memarray->unused = used->memitem;
		memarray->n_unused += used->memitem->n_used;
		if (used->memitem->i_memarray < memanager->i_available)
			memanager->i_available = used->memitem->i_memarray;
		used->oldest = used->oldest->next_oldest;
		used->memitem = used->newest;
		if (used->newest)
			used->newest = used->newest->next_newest;
		else if (used->oldest)
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
	used->memitem->next_newest = used->newest;
	used->newest = used->memitem;
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
