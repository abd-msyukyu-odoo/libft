/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 14:22:22 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/09 12:49:08 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char		*out;

	if (s == NULL)
		return (NULL);
	out = ft_strnew(len);
	if (out == NULL)
		return (out);
	return ((char *)ft_memmove(out, s + (size_t)start, len));
}
