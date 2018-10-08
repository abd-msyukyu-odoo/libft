/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 12:29:51 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/08 12:43:45 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strnequ(const char *s1, const char *s2, size_t n)
{
	if (s1 == NULL)
	{
		if (s2 == NULL)
			return (1);
		return (0);
	}
	else if (s2 == NULL)
		return (0);
	return (ft_strncmp(s1, s2, n) == 0);
}
