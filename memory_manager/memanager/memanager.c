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
	if (!sizes || addresses < sizes || chunk_size < addresses ||
		chunk_size < sizeof(t_memjump))
		return (-1); // general dimensions condition
	if (addresses / 3 < sizes)
		return (-2); // btree condition (at least 1 address per size + 2 non-set childs)
	if (chunk_size - addresses < sizeof(t_memjump) ||
		(chunk_size - addresses - sizeof(t_memjump)) / sizeof(t_memjump) <
		sizes)
		return (-3); // underflow condition
	if (sizes > (size_t)1 << (sizeof(size_t) / 2 + 1))
		return (-4); // overflow condition
	if (chunk_size - addresses - sizeof(t_memjump) - sizeof(t_memjump) * sizes <
		sizes / 2 * (sizes - 1))
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

t_memanager				*ft_memanager_construct(size_t sizes, size_t addresses,
	size_t chunk_size)
{
	t_memanager			*out;
	if (ft_memanager_validate_amounts(sizes, addresses, chunk_size) < 0)
		return (NULL);
	out = (t_memanager*)malloc(sizeof(t_memanager));
	if (!out)
		return (NULL);
	if (!ft_memanager_initialize(out, sizes, addresses, chunk_size))
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
