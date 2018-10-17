/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 16:40:33 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/17 10:08:34 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int			ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n && s1[i] != '\0' &&
			(unsigned char)s1[i] - (unsigned char)s2[i] == 0)
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
