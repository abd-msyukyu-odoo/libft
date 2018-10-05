/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 15:06:31 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/05 15:13:17 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strdup(const char *s1)
{
	char		*out;
	size_t		i;

	out = malloc(sizeof(char) + ft_strlen(s1));
	if (out == NULL)
		return (out);
	i = -sizeof(char);
	while (s1[++i] != '\0')
		out[i] = s1[i];
	out[i] = '\0';
	return (out);
}
