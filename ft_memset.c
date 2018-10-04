/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 13:05:56 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/04 13:44:40 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void		*ft_memset(void *b, int c, size_t len)
{
	unsigned char	byte;
	size_t			i;
	char			*head;

	byte = (unsigned char)c;
	i = 0;
	head = b;
	while (i < len)
		*(head + i++) = byte;
	return (head);
}
