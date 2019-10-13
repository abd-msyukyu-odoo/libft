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
	if (chunk_size - addresses < sizeof(t_memstart) ||
		(chunk_size - addresses - sizeof(t_memstart)) / sizeof(t_memjump) <
		sizes)
		return (-3); // underflow condition
	if (sizes > (size_t)1 << (sizeof(size_t) / 2 + 1))
		return (-4); // overflow condition
	if (chunk_size - addresses - sizeof(t_memstart) - sizeof(t_memjump) * sizes
		< sizes / 2 * (sizes - 1))
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
	stbtree->typeitem = memanager->stbtree_used.last;
	if (!(stbtree->addr_tbt = ft_typemanager_get(memanager->tbtree_mng,
		&memanager->tbtree_used)) ||
		1 > ft_tbtree_construct(stbtree->addr_tbt, memanager->tbnode_mng,
		ft_btree_cmp_addr))
		return (NULL);
	return (stbtree);
}

static int				ft_memanager_add_addr(t_memanager *memanager,
	void *addr, size_t sizeof_addr)
{
	t_stbtree			*stbtree;

	if (!(stbtree = ft_btree_get(memanager->stbtree_tbt, &sizeof_addr)) &&
		!(stbtree = ft_stbtree_construct(memanager, sizeof_addr)))
		return (0);
	return (ft_tbtree_add(stbtree, addr));
}

static int				ft_memanager_initalize_memarray(t_memanager *memanager,
	size_t i_memarray)
{
	t_array				*memarray;
	t_memstart			*start;
	t_memjump			*end;

	memarray = *(t_array**)ft_array_get(memanager->memarrays, 0);
	memarray->n_items = memarray->size;
	start = (t_memstart*)ft_array_get(memarray, 0);
	end = (t_memjump*)ft_array_get(memarray,
		memarray->size - sizeof(t_memjump));
	start->memjump.prev = NULL;
	end->next = NULL;
	start->memjump.next = end;
	end->prev = (t_memjump*)start;
	return (ft_memanager_add_addr(memanager,
		ft_array_get(memarray, sizeof(t_memstart)),
		memarray->size - sizeof(t_memjump) - sizeof(t_memstart)));
}

static int				ft_memanager_initialize_stbtree(t_memanager *memanager)
{
	if (!(memanager->stbtree_tbt = ft_typemanager_get(memanager->tbtree_mng,
		&memanager->tbtree_used)))
		return (0);
	return (ft_tbtree_construct(memanager->stbtree_tbt, memanager->tbnode_mng,
		ft_btree_cmp_size));
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
		1 > ft_memanager_initialize_memarray(out, 0))
		return (ft_memanager_error(out));
	return (out);
}

t_memanager				*ft_memanager_construct_default(void)
{
	return (ft_memanager_construct(MMNG_DEFAULT_SIZE_COUNT,
		MMNG_DEFAULT_ADDR_COUNT,
		MMNG_DEFAULT_CHUNK_SIZE));
}

//add method to extend size depending on external request -> custom block if very big
