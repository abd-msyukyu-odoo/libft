/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 16:00:44 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/09 13:39:22 by dabeloos         ###   ########.fr       */
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
	i = -1;
	while (s[++i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c &&
				s[i + 1] != '\0')
			splitsize += sizeof(char *);
	}
	return (splitsize);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**out;
	size_t		i;
	size_t		words;
	size_t		len_word;

	out = (char **)ft_memalloc(ft_strsplitsize(s, c));
	if (out == NULL)
		return (out);
	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			++i;
		if (s[i] == '\0')
			break ;
		len_word = 0;
		while (s[i + len_word] != c && s[i + len_word] != '\0')
			++len_word;
		if (len_words > 0)
			if ((out[words++] = ft_strsub2(s, i, len_word)) == NULL)
				return (NULL);
		i += len_words;
	}
	return (out);
}
