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

static int				ft_memanager_validate_amounts(size_t sizes,
	size_t addresses, size_t chunk_size)
{
	if (!sizes || addresses < 2 || !chunk_size)
		return (-1);
	if (addresses / 3 < sizes)
		return (-2);
	//verifier qu'on peut contenir sizes differentes avec addresses separees par
	//des memjumps (trop severe) -> ajuster en interne ?
	if (chunk_size / sizes * 2 - 1 < sizes)
		return (-3);
	return (1);
}

t_memanager				*ft_memanager_construct(size_t sizes, size_t addresses,
	size_t chunk_size)
{
	
}

t_memanager				*ft_memanager_construct_default(void)
{
	return (ft_memanager_construct(MMNG_DEFAULT_SIZE_COUNT,
		MMNG_DEFAULT_ADDR_COUNT,
		MMNG_DEFAULT_CHUNK_SIZE));
}
