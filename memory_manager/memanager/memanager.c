/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memanager.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:35:40 by dabeloos          #+#    #+#             */
/*   Updated: 2019/09/27 16:35:41 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int						ft_memanager_validate_amounts(size_t sizes,
	size_t addresses, size_t chunk_size, size_t overlap)
{
	if (!sizes || addresses < sizes || chunk_size < addresses ||
		overlap < addresses / sizes || overlap > addresses)
		return (-1);
	if (addresses / 3 < sizes)
		return (-2);
	if (chunk_size - addresses < 3 * sizeof(t_memjump) + sizeof(size_t) ||
		(chunk_size - addresses - sizeof(t_memjump) - sizeof(size_t)) /
		sizeof(t_memjump) < sizes)
		return (-3);
	if (sizes > ((size_t)1 << (4 * sizeof(size_t) + 1)))
		return (-4);
	if (chunk_size - addresses - sizeof(t_memjump) - sizeof(size_t) -
		sizeof(t_memjump) * sizes < sizes / 2 * (sizes - 1))
		return (-5);
	return (1);
}

void					ft_memanager_free(t_memanager *mmng)
{
	size_t				i;

	if (!mmng)
		return ;
	if (mmng->memarrays)
	{
		i = 0;
		while (i < mmng->memarrays->n_items)
		{
			ft_array_free(*(t_array**)ft_array_get(mmng->memarrays, i));
			++i;
		}
		ft_array_free(mmng->memarrays);
	}
	if (mmng->sthm_mng)
		ft_typemanager_free(mmng->sthm_mng);
	if (mmng->array_mng)
		ft_typemanager_free(mmng->array_mng);
	if (mmng->items_mng)
		ft_typemanager_free(mmng->items_mng);
	if (mmng->tbnode_mng)
		ft_typemanager_free(mmng->tbnode_mng);
	free(mmng);
}

static t_memanager		*ft_memanager_error(t_memanager *mmng)
{
	ft_memanager_free(mmng);
	return (NULL);
}

static void				ft_tarray_tbtree_initialize(t_array *array, size_t size)
{
	array->n_items = size;
	array->size = size;
	array->sizeof_item = sizeof(t_tbtree);
	ft_bzero(array->items, size * array->sizeof_item);
}

static t_sthmap			*ft_sthmap_construct(t_memanager *mmng, size_t size)
{
	t_sthmap			*sthmap;
	t_array				*array;

	if (!size)
		return (NULL);
	if (!(sthmap = ft_typemanager_get(mmng->sthm_mng,
		&mmng->sthm_used)))
		return (NULL);
	sthmap->sthm_typeitem = mmng->sthm_used.last;
	sthmap->size.key = size;
	if (!(array = ft_typemanager_get_typeitem(mmng->array_mng,
		&mmng->array_used, &sthmap->array_typeitem)) ||
		!(array->items = ft_typemanager_get_typeitem(mmng->items_mng,
		&mmng->items_used, &sthmap->items_typeitem)))
		return (NULL);
	ft_tarray_tbtree_initialize(array, mmng->overlap);
	ft_thmap_initialize(&sthmap->addr_thmap, mmng->tbnode_mng, array,
		ft_hmap_hash_addr);
	return (sthmap);
}

static void				ft_sthmap_refill(t_memanager *mmng, t_sthmap *sthmap)
{
	ft_thmap_refill(&sthmap->addr_thmap);
	ft_typeused_recover(&mmng->array_used, sthmap->array_typeitem);
	ft_typeused_recover(&mmng->items_used, sthmap->items_typeitem);
	ft_typeused_recover(&mmng->sthm_used, sthmap->sthm_typeitem);
}

static int				ft_memanager_add_addr(t_memanager *mmng,
	void *addr, size_t sizeof_addr)
{
	t_sthmap			*sthmap;
	t_tbnode			*stbnode;

	stbnode = (t_tbnode*)ft_btree_get_bnode((t_btree*)&mmng->sthmap_tbt,
		&sizeof_addr);
	if (!stbnode->bnode.rank &&
		(!(sthmap = ft_sthmap_construct(mmng, sizeof_addr)) ||
			(1 > ft_tbtree_add_ext_tbnode(&mmng->sthmap_tbt, stbnode, sthmap))))
		return (0);
	else
		sthmap = (t_sthmap*)stbnode->bnode.named;
	return (ft_thmap_add(&sthmap->addr_thmap, addr));
}

static t_array			*ft_memanager_initialize_memarray(
	t_memanager *mmng, size_t i_memarray)
{
	t_array				*memarray;
	t_memjump			*start;
	t_memjump			*end;
	size_t				*i_memarray_p;

	memarray = *(t_array**)ft_array_get(mmng->memarrays, i_memarray);
	memarray->n_items = memarray->size;
	i_memarray_p = (size_t*)ft_array_get(memarray, 0);
	start = (t_memjump*)ft_array_get(memarray, sizeof(size_t));
	end = (t_memjump*)ft_array_get(memarray,
		memarray->size - sizeof(t_memjump));
	if (!i_memarray_p || !start || !end)
		return (NULL);
	*i_memarray_p = i_memarray;
	start->prev = NULL;
	end->next = NULL;
	start->next = end;
	end->prev = start;
	return (memarray);
}

static int				ft_memanager_initialize_first_memarray(
	t_memanager *mmng)
{
	t_array				*memarray;

	memarray = ft_memanager_initialize_memarray(mmng, 0);
	return (ft_memanager_add_addr(mmng,
		ft_array_get(memarray, sizeof(t_memjump) + sizeof(size_t)),
		memarray->size - 2 * sizeof(t_memjump) - sizeof(size_t)));
}

static int				ft_memanager_initialize_sthmap_tbt(t_memanager *mmng)
{
	return (ft_tbtree_initialize(&mmng->sthmap_tbt, mmng->tbnode_mng,
		ft_btree_cmp_size));
}

static int				ft_memanager_initialize(t_memanager *mmng)
{
	ft_typeused_initialize(&mmng->sthm_used);
	ft_typeused_initialize(&mmng->array_used);
	ft_typeused_initialize(&mmng->items_used);
	return (1 <= ft_memanager_initialize_sthmap_tbt(mmng) &&
		1 <= ft_memanager_initialize_first_memarray(mmng));
}

static int				ft_memanager_internal_construct(t_memanager *mmng,
	size_t sizes, size_t addresses)
{
	t_array				**injector;

	return ((mmng->sthm_mng = ft_typemanager_construct(sizes,
			sizeof(t_sthmap))) &&
		(mmng->array_mng = ft_typemanager_construct(sizes,
			sizeof(t_array))) &&
		(mmng->items_mng = ft_typemanager_construct(sizes,
			sizeof(t_tbtree) * mmng->overlap)) &&
		(mmng->tbnode_mng = ft_typemanager_construct(addresses +
			sizes * mmng->overlap, sizeof(t_tbnode))) &&
		(mmng->memarrays = ft_array_construct(1, sizeof(t_array*))) &&
		(injector = (t_array**)ft_array_inject(mmng->memarrays)) &&
		(*injector = ft_array_construct(mmng->chunk_size, sizeof(char))));
}

t_memanager				*ft_memanager_construct(size_t sizes, size_t addresses,
	size_t chunk_size, size_t overlap)
{
	t_memanager			*out;

	if (ft_memanager_validate_amounts(sizes, addresses, chunk_size,
		overlap) < 0)
		return (NULL);
	out = (t_memanager*)malloc(sizeof(t_memanager));
	if (!out)
		return (NULL);
	out->chunk_size = chunk_size;
	out->overlap = overlap;
	if (!ft_memanager_internal_construct(out, sizes, addresses) ||
		!ft_memanager_initialize(out))
		return (ft_memanager_error(out));
	return (out);
}

t_memanager				*ft_memanager_construct_default(void)
{
	return (ft_memanager_construct(MMNG_DEFAULT_ADDR_COUNT,
		MMNG_DEFAULT_ADDR_COUNT,
		MMNG_DEFAULT_ADDR_COUNT,
		MMNG_DEFAULT_OVRLP_SIZE));
}

t_array					*ft_memanager_extend_size(
	t_memanager *mmng, size_t chunk_size)
{
	t_array				**injector;

	if (!mmng)
		return (NULL);
	if (!(injector = (t_array**)ft_array_inject(mmng->memarrays)) ||
		!(*injector = ft_array_construct(chunk_size, sizeof(char))))
		return (NULL);
	return (ft_memanager_initialize_memarray(mmng,
		mmng->memarrays->n_items - 1));
}
