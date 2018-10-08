/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 12:21:21 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/08 12:24:14 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char		*out;
	size_t		i;

	if (s == NULL || f == NULL)
		return (NULL);
	out = ft_strnew(ft_strlen(s));
	if (out == NULL)
		return (out);
	i = 0;
	while (s[i] != '\0')
	{
		out[i] = f((unsigned int)i, s[i]);
		if ((unsigned int)++i == 0)
			return (out);
	}
	return (out);
}
