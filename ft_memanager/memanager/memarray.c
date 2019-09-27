#include "memanager.h"

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
