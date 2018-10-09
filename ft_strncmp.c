/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 16:40:33 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/09 12:43:46 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int			ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t		i;
	int			r;

	r = 0;
	i = -1;
	while (s1[++i] != '\0' && s2[i] != '\0' && r == 0 && i < n)
		r = (unsigned char)s1[i] - (unsigned char)s2[i];
	if (i == n)
		return (r);
	return ((r == 0) ? (unsigned char)s1[i] - (unsigned char)s2[i] : r);
}
