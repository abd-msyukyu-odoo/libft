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
		return (-1); // general dimensions condition
	if (addresses / 3 < sizes)
		return (-2); // btree condition (at least 1 address per size + 2 non-set childs)
	if (chunk_size - addresses < 3 * sizeof(t_memjump) + sizeof(size_t) ||
		(chunk_size - addresses - sizeof(t_memjump) - sizeof(size_t)) /
		sizeof(t_memjump) < sizes)
		return (-3); // underflow condition -> 1st condition : see get_extended (3 jumpers)
	if (sizes > ((size_t)1 << (4 * sizeof(size_t) + 1)))
		return (-4); // overflow condition
	if (chunk_size - addresses - sizeof(t_memjump) - sizeof(size_t) -
		sizeof(t_memjump) * sizes < sizes / 2 * (sizes - 1))
		return (-5); // chunk_size is too small compared to sizes & addresses
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
	if (!(sthmap = ft_typemanager_get_typeitem(mmng->sthm_mng,
		&mmng->sthm_used, &sthmap->sthm_typeitem)))
		return (NULL);
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

static int				ft_memanager_add_addr(t_memanager *mmng,
	void *addr, size_t sizeof_addr)
{
	t_sthmap			*sthmap;
	t_tbnode			*stbnode;

	stbnode = ft_btree_get_bnode((t_btree*)&mmng->sthmap_tbt,
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
	ft_typeused_initialize(&mmng->thm_used);
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

//ICI -> probleme lie aux hmap en general :
// meilleure facon de pouvoir sortir le premier element possible de la hashmap?
// comment savoir si la hasmap est completement vide
// arbre binaire des hash utilises a mettre a jour pour chaque add et remove
static void				*ft_memanager_get_as_is(t_memanager *mmng,
	t_tbnode *tbnode_sthmap)
{
	t_sthmap			*sthmap;
	t_tbtree			*stbtree;
	t_tbnode			*tbnode_addr;

	sthmap = (t_sthmap*)tbnode_sthmap->bnode.named;
	stbtree = (t_tbtree*)ft_hmap_get(&sthmap->addr_thmap, )
	tbnode_addr = ft_thmap_
}

static int				ft_memanager_set_cut(t_memanager *mmng,
	size_t sizeof_item, void *out)
{
	t_memjump			*start;
	t_memjump			*step;
	t_memjump			*end;
	void				*cut;

	start = (t_memjump*)((char*)out - sizeof(t_memjump));
	step = (t_memjump*)((char*)out + sizeof_item);
	end = start->next;
	start->next = step;
	step->prev = start;
	step->next = end;
	end->prev = step;
	cut = (void*)((char*)step + sizeof(t_memjump));
	return (ft_memanager_add_addr(mmng, cut,
		(size_t)((char*)end - (char*)cut)));
}

static void				*ft_memanager_get_cut(t_memanager *mmng,
	size_t sizeof_item, t_tbnode *tbnode_sthmap)
{
	void				*out;

	out = ft_memanager_get_as_is(mmng, tbnode_sthmap);
	if (!ft_memanager_set_cut(mmng, sizeof_item, out))
		return (NULL);
	return (out);
}

static void				*ft_memanager_get_extended(t_memanager *mmng,
	size_t sizeof_item)
{
	t_array				*memarray;
	void				*out;

	if (sizeof_item > mmng->chunk_size - sizeof(size_t) -
		3 * sizeof(t_memjump) - 1)
	{
		if (!(memarray = ft_memanager_extend_size(mmng,
			sizeof_item + 2 * sizeof(t_memjump) + sizeof(size_t))))
			return (NULL);
		out = ft_array_get(memarray, sizeof(size_t) + sizeof(t_memjump));
		return (out);
	}
	if (!(memarray = ft_memanager_extend_size(mmng, mmng->chunk_size)))
		return (NULL);
	out = ft_array_get(memarray, sizeof(size_t) + sizeof(t_memjump));
	if (!ft_memanager_set_cut(mmng, sizeof_item, out))
		return (NULL);
	return (out);
}

void					*ft_memanager_get(t_memanager *mmng,
	size_t sizeof_item)
{
	//parcourir les tailles dans le btree
		//des qu'on prend a gauche on enregistre en tampon le dernier parent
			//on trouve -> cours normal
			//on ne trouve pas + pas de parent -> extend size (peut etre custom)
			//on ne trouve pas + parent -> decoupage de pointeur + ajout du reste
				//si reste <= sizeof(t_memjump) -> pas de decoupage
		//dans les 3 cas : retrait de l'addresse (ou non-ajout /!\)
	t_tbnode			*tbnode_sthmap;

	if (!mmng || !sizeof_item)
		return (NULL);
	tbnode_sthmap = (t_tbnode*)ft_btree_get_min_equal_or_greater_bnode(
		(t_btree*)&mmng->sthmap_tbt, &sizeof_item);
	if (!tbnode_sthmap->bnode.rank)
		return (ft_memanager_get_extended(mmng, sizeof_item));
	if (((t_sthmap*)tbnode_sthmap->bnode.named)->size.key - sizeof_item >
		sizeof(t_memjump))
		return (ft_memanager_get_cut(mmng, sizeof_item, tbnode_sthmap));
	return (ft_memanager_get_as_is(mmng, tbnode_sthmap));
}