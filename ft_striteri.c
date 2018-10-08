/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 11:38:37 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/08 11:51:48 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t		i;

	if (s == NULL || f == NULL)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		f((unsigned int)i, s + i);
		if ((unsigned int)++i == 0)
			return ;
	}
}
