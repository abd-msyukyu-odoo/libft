/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 20:02:47 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/11 16:54:31 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void		*ft_memalloc(size_t size)
{
	unsigned char	*out;
	size_t			i;

	if (size == 0)
		return (NULL);
	out = (unsigned char *)malloc(size);
	if (out == NULL)
		return (out);
	i = -1;
	while (++i < size)
		out[i] = 0;
	return (out);
}
