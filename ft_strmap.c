/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 11:58:34 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/08 12:19:14 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(const char *s, char (*f)(char))
{
	char		*out;
	size_t		i;

	if (s == NULL || f == NULL)
		return (NULL);
	out = ft_strnew(ft_strlen(s));
	if (out == NULL)
		return (out);
	i = -sizeof(char);
	while (s[++i] != '\0')
		out[i] = f(s[i]);
	return (out);
}
