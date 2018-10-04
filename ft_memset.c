/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 13:05:56 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/04 15:53:51 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void		*ft_memset(void *b, int c, size_t len)
{
	unsigned char	check;
	size_t			i;
	unsigned char	*d;

	check = (unsigned char)c;
	i = 0;
	d = (unsigned char *)b;
	while (i < len)
		*(d + i++) = check;
	return (b);
}
