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
	size_t addresses, size_t chunk_size)
{
	if (!sizes || addresses < sizes || chunk_size < addresses)
		return (-1); // general dimensions condition
	if (addresses / 3 < sizes)
		return (-2); // btree condition (at least 1 address per size + 2 non-set childs)
	if (chunk_size - addresses < 3 * sizeof(t_memjump) + sizeof(size_t) ||
		(chunk_size - addresses - sizeof(t_memjump) - sizeof(size_t)) /
		sizeof(t_memjump) < sizes)
		return (-3); // underflow condition -> 1st condition : see get_extended (3 jumpers)
	if (sizes > (size_t)1 << (sizeof(size_t) / 2 + 1))
		return (-4); // overflow condition
	if (chunk_size - addresses - sizeof(t_memjump) - sizeof(size_t) -
		sizeof(t_memjump) * sizes < sizes / 2 * (sizes - 1))
		return (-5); // chunk_size is too small compared to sizes & addresses
	return (1);
}

void					ft_memanager_free(t_memanager *memanager)
{
	size_t				i;

	if (!memanager)
		return ;
	if (memanager->memarrays)
	{
		i = 0;
		while (i < memanager->memarrays->n_items)
		{
			ft_array_free(*(t_array**)ft_array_get(memanager->memarrays, i));
			++i;
		}
		ft_array_free(memanager->memarrays);
	}
	if (memanager->stbtree_mng)
		ft_typemanager_free(memanager->stbtree_mng);
	if (memanager->tbtree_mng)
		ft_typemanager_free(memanager->tbtree_mng);
	if (memanager->tbnode_mng)
		ft_typemanager_free(memanager->tbnode_mng);
	free(memanager);
}

static t_memanager		*ft_memanager_error(t_memanager *memanager)
{
	ft_memanager_free(memanager);
	return (NULL);
}

static t_stbtree		*ft_stbtree_construct(t_memanager *memanager,
	size_t size)
{
	t_stbtree			*stbtree;

	if (!size)
		return (NULL);
	if (!(stbtree = ft_typemanager_get(memanager->stbtree_mng,
		&memanager->stbtree_used)))
		return (NULL);
	stbtree->size.key = size;
	stbtree->stbt_typeitem = memanager->stbtree_used.last;
	if (!(stbtree->addr_tbt = ft_typemanager_get(memanager->tbtree_mng,
		&memanager->tbtree_used)) ||
		1 > ft_tbtree_construct(stbtree->addr_tbt, memanager->tbnode_mng,
		ft_btree_cmp_addr))
		return (NULL);
	stbtree->tbt_typeitem = memanager->tbtree_used.last;
	return (stbtree);
}

static int				ft_memanager_add_addr(t_memanager *memanager,
	void *addr, size_t sizeof_addr)
{
	t_stbtree			*stbtree;

	if (!(stbtree = ft_btree_get((t_btree*)memanager->stbtree_tbt,
		&sizeof_addr)) &&
		(!(stbtree = ft_stbtree_construct(memanager, sizeof_addr)) ||
		(1 > ft_tbtree_add(memanager->stbtree_tbt, stbtree))))
		return (0);
	return (ft_tbtree_add(stbtree->addr_tbt, addr));
}

static t_array			*ft_memanager_initialize_memarray(
	t_memanager *memanager, size_t i_memarray)
{
	t_array				*memarray;
	t_memjump			*start;
	t_memjump			*end;
	size_t				*i_memarray_p;

	memarray = *(t_array**)ft_array_get(memanager->memarrays, 0);
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
	t_memanager *memanager, size_t i_memarray)
{
	t_array				*memarray;

	memarray = ft_memanager_initialize_memarray(memanager, i_memarray);
	return (ft_memanager_add_addr(memanager,
		ft_array_get(memarray, sizeof(t_memjump) + sizeof(size_t)),
		memarray->size - 2 * sizeof(t_memjump) - sizeof(size_t)));
}

static int				ft_memanager_initialize_stbtree(t_memanager *memanager)
{
	if (!(memanager->stbtree_tbt = ft_typemanager_get(memanager->tbtree_mng,
		&memanager->tbtree_used)))
		return (0);
	return (ft_tbtree_construct(memanager->stbtree_tbt, memanager->tbnode_mng,
		ft_btree_cmp_size));
}

t_array					*ft_memanager_extend_size(
	t_memanager *memanager, size_t chunk_size)
{
	t_array				**injector;

	if (!(injector = (t_array**)ft_array_inject(memanager->memarrays)) ||
		!(*injector = ft_array_construct(chunk_size, sizeof(char))))
		return (NULL);
	return (ft_memanager_initialize_memarray(memanager,
		memanager->memarrays->n_items - 1));
}

t_memanager				*ft_memanager_construct(size_t sizes, size_t addresses,
	size_t chunk_size)
{
	t_memanager			*out;
	t_array				**injector;

	if (ft_memanager_validate_amounts(sizes, addresses, chunk_size) < 0)
		return (NULL);
	out = (t_memanager*)malloc(sizeof(t_memanager));
	if (!out)
		return (NULL);
	if (!(out->tbtree_mng = ft_typemanager_construct(sizes + 1,
		sizeof(t_tbtree))) ||
		!(out->tbnode_mng = ft_typemanager_construct(sizes + addresses,
		sizeof(t_tbnode))) ||
		!(out->stbtree_mng = ft_typemanager_construct(sizes,
		sizeof(t_stbtree))) ||
		!(out->memarrays = ft_array_construct(1, sizeof(t_array*))) ||
		!(injector = (t_array**)ft_array_inject(out->memarrays)) ||
		!(*injector = ft_array_construct(chunk_size, sizeof(char))))
		return (ft_memanager_error(out));
	ft_typeused_initialize(&out->stbtree_used);
	ft_typeused_initialize(&out->tbtree_used);
	out->chunk_size = chunk_size;
	if (1 > ft_memanager_initialize_stbtree(out) ||
		1 > ft_memanager_initialize_first_memarray(out, 0))
		return (ft_memanager_error(out));
	return (out);
}

t_memanager				*ft_memanager_construct_default(void)
{
	return (ft_memanager_construct(MMNG_DEFAULT_SIZE_COUNT,
		MMNG_DEFAULT_ADDR_COUNT,
		MMNG_DEFAULT_CHUNK_SIZE));
}

static void				*ft_memanager_get_as_is(t_memanager *memanager,
	t_tbnode *tbnode_stbtree)
{
	t_stbtree			*stbtree;
	t_tbnode			*container;
	void				*out;

	stbtree = (t_stbtree*)tbnode_stbtree->bnode.named;
	container = ft_tbtree_remove_ext_tbnode(stbtree->addr_tbt,
		(t_tbnode*)stbtree->addr_tbt->btree.root);
	out = container->bnode.named;
	if (!stbtree->addr_tbt->btree.root->rank)
	{
		tbnode_stbtree = ft_tbtree_remove_ext_tbnode(memanager->stbtree_tbt,
			tbnode_stbtree);
		ft_typeused_recover(&memanager->stbtree_tbt->tused,
			tbnode_stbtree->typeitem);
		ft_typemanager_refill(stbtree->addr_tbt->tmng,
			&stbtree->addr_tbt->tused);
		ft_typeused_recover(&memanager->stbtree_used, stbtree->stbt_typeitem);
		ft_typeused_recover(&memanager->tbtree_used, stbtree->tbt_typeitem);
	}
	else
		ft_typeused_recover(&stbtree->addr_tbt->tused, container->typeitem);
	return (out);
}

static int				ft_memanager_set_cut(t_memanager *memanager,
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
	return (ft_memanager_add_addr(memanager, cut,
		(size_t)((char*)end - (char*)cut)));
}

static void				*ft_memanager_get_cut(t_memanager *memanager,
	size_t sizeof_item, t_tbnode *tbnode_stbtree)
{
	void				*out;

	out = ft_memanager_get_as_is(memanager, tbnode_stbtree);
	if (!ft_memanager_set_cut(memanager, sizeof_item, out))
		return (NULL);
	return (out);
}

static void				*ft_memanager_get_extended(t_memanager *memanager,
	size_t sizeof_item)
{
	t_array				*memarray;
	void				*out;

	if (sizeof_item > memanager->chunk_size - sizeof(size_t) -
		3 * sizeof(t_memjump) - 1)
	{
		if (!(memarray = ft_memanager_extend_size(memanager,
			sizeof_item + 2 * sizeof(t_memjump) + sizeof(size_t))))
			return (NULL);
		out = ft_array_get(memarray, sizeof(size_t) + sizeof(t_memjump));
		return (out);
	}
	if (!(memarray = ft_memanager_extend_size(memanager,
		memanager->chunk_size)))
		return (NULL);
	out = ft_array_get(memarray, sizeof(size_t) + sizeof(t_memjump));
	if (!ft_memanager_set_cut(memanager, sizeof_item, out))
		return (NULL);
	return (out);
}

void					*ft_memanager_get(t_memanager *memanager,
	size_t sizeof_item)
{
	//parcourir les tailles dans le btree
		//des qu'on prend a gauche on enregistre en tampon le dernier parent
			//on trouve -> cours normal
			//on ne trouve pas + pas de parent -> extend size (peut etre custom)
			//on ne trouve pas + parent -> decoupage de pointeur + ajout du reste
				//si reste <= sizeof(t_memjump) -> pas de decoupage
		//dans les 3 cas : retrait de l'addresse (ou non-ajout /!\)
	t_tbnode			*tbnode_stbtree;

	tbnode_stbtree = (t_tbnode*)ft_btree_get_min_equal_or_greater_bnode(
		(t_btree*)memanager->stbtree_tbt, &sizeof_item);
	if (!tbnode_stbtree->bnode.rank)
		return (ft_memanager_get_extended(memanager, sizeof_item));
	if (((t_stbtree*)tbnode_stbtree->bnode.named)->size.key - sizeof_item >
		sizeof(t_memjump))
		return (ft_memanager_get_cut(memanager, sizeof_item, tbnode_stbtree));
	return (ft_memanager_get_as_is(memanager, tbnode_stbtree));
}

static t_memjump		*ft_memanager_refill_right(t_memanager *memanager,
	void *addr)
{
	void				*out;
	t_memjump			*start;
	t_memjump			*end;
	t_tbnode			*tbnode_stbtree;
	size_t				sizeof_out;

	start = (t_memjump*)((char*)addr - sizeof(t_memjump));
	start = start->next;
	if (!(end = start->next))
		return (start);
	out = (void*)((char*)start + sizeof(t_memjump));
	sizeof_out = (size_t)((char*)end - (char*)out);
	tbnode_stbtree = (t_tbnode*)ft_btree_get_bnode(
		(t_btree*)memanager->stbtree_tbt, &sizeof_out);
	if (!tbnode_stbtree->bnode.rank)
		return (start);
	ft_memanager_get_as_is(memanager, tbnode_stbtree);
	return (end);
}

static t_memjump		*ft_memanager_refill_left(t_memanager *memanager,
	void *addr)
{
	void				*out;
	t_memjump			*end;
	t_memjump			*start;
	t_tbnode			*tbnode_stbtree;
	size_t				sizeof_out;

	end = (t_memjump*)((char*)addr - sizeof(t_memjump));
	if (!(start = end->prev))
		return (end);
	out = (void*)((char*)start + sizeof(t_memjump));
	sizeof_out = (size_t)((char*)end - (char*)out);
	tbnode_stbtree = (t_tbnode*)ft_btree_get_bnode(
		(t_btree*)memanager->stbtree_tbt, &sizeof_out);
	if (!tbnode_stbtree->bnode.rank)
		return (end);
	ft_memanager_get_as_is(memanager, tbnode_stbtree);
	return (start);
}

int						ft_memanager_refill(t_memanager *memanager, void *addr)
{
	t_memjump			*left;
	t_memjump			*right;
	size_t				*i_memarray_p;
	size_t				*i_new_memarray_p;
	t_array				**memarray;

	left = ft_memanager_refill_left(memanager, addr);
	right = ft_memanager_refill_right(memanager, addr);
	left->next = right;
	right->prev = left;
	addr = (void*)((char*)left + sizeof(t_memjump));
	if (!left->prev && !right->next)
	{
		i_memarray_p = (size_t*)((char*)left - sizeof(size_t));
		memarray = (t_array**)ft_array_get(memanager->memarrays, *i_memarray_p);
		ft_array_free(*memarray);
		*memarray = NULL;
		ft_array_remove(memanager->memarrays,
			memanager->memarrays->n_items - 1, (void*)memarray);
		i_new_memarray_p = (size_t*)ft_array_get(*memarray, 0);
		*i_new_memarray_p = *i_memarray_p;
		return (2);
	}
	return (ft_memanager_add_addr(memanager, addr,
		(size_t)((char*)right - (char*)addr)));
}
