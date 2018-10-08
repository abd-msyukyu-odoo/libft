/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 15:06:31 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/08 13:41:45 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s1)
{
	char		*out;
	size_t		i;

	out = ft_strnew(ft_strlen(s1));
	if (out == NULL)
		return (out);
	i = -sizeof(char);
	while (s1[++i] != '\0')
		out[i] = s1[i];
	return (out);
}
