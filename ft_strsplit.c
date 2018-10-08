/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 16:00:44 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/08 16:50:25 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strsplitsize(char const *s, char c)
{
	size_t		i;
	size_t		splitsize;

	splitsize = sizeof(char *);
	if (s == NULL)
		return (splitsize);
	i = -sizeof(char);
	while (s[++i] != '\0')
	{
		if (s[i] == c && s[i + sizeof(char)] != c &&
				s[i + sizeof(char)] != '\0')
			splitsize += sizeof(char *);
	}
	return (splitsize);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**out;

	out = (char **)malloc(ft_strsplitsize(s, c));
	if (out == NULL)
		return (out);
	
}
