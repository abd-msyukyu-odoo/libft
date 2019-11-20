/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 20:36:21 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 20:36:22 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t				ft_hmap_hash_ascii(void *s, size_t size)
{
	char			*in;
	unsigned long	hash;
	unsigned int	c;

	hash = 5381;
	in = (char*)s;
	while (c = (unsigned int)*in++)
		hash = ((hash << 5) + hash) + c;
	return (hash % size);
}

size_t				ft_hmap_hash_nbr(void *s, size_t size)
{
	return (*(size_t*)s % size);
}

size_t				ft_hmap_hash_addr(void *s, size_t size)
{
	return ((uintmax_t)s % size);
}
