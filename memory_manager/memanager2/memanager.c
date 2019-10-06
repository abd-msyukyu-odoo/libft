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

#include "memory_manager/memanager2.h"
#include "libft.h"

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

t_memanager					*ft_memanager_construct(size_t memory)
{
	t_memanager				*out;
	t_memarray				**injector;

	out = (t_memanager*)malloc(sizeof(t_memanager));
	if (!out || !(out->memarrays = ft_array_construct(1, sizeof(t_memarray*)))
		|| !(injector = (t_memarray**)ft_array_inject(out->memarrays))
		|| !(*injector = ft_memarray_construct(memory / sizeof(char),
			sizeof(char), 0)))
		return (ft_memanager_error(out));
	out->i_available = 0;
	return (out);
}

int							ft_memanager_extend_size(t_memanager *memanager,
	size_t memory_extension)
{
	t_memarray				**injector;

	injector = (t_memarray**)ft_array_inject(memanager->memarrays);
	if (!injector || !(*injector = ft_memarray_construct(memory_extension)))
		return (0);
	return (1);
}
