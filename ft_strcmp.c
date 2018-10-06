/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 16:20:12 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/06 16:34:40 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strcmp(const char *s1, const char *s2)
{
	size_t		i;
	int			r;

	r = 0;
	i = -sizeof(char);
	while (s1[++i] != '\0' && s2[i] != '\0' && r == 0)
		r = (unsigned char)s1[i] - (unsigned char)s2[i];
	return ((r == 0) ? (unsigned char)s1[i] - (unsigned char)s2[i] : r);
}
