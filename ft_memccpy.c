/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 15:14:22 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/04 15:52:48 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;
	unsigned char	check;

	i = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	check = (unsigned char)c;
	while (i < n && *(s + i) != check)
	{
		*(d + i) = *(s + i);
		++i;
	}
	if (*(s + i) == check)
	{
		*(d + i) = check;
		return (dst + i + 1);
	}
	return (NULL);
}
