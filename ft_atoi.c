/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 16:51:58 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/06 19:04:53 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	long		result;
	size_t		i;
	char		sign;
	long		tmp;

	result = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		++i;
	if (str[i] == '+' || (str[i] == '-' && (sign = -1)))
		++i;
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = result;
		result = result * 10 + sign * (str[i++] - '0');
		if (tmp != 0 && (tmp ^ result) < 0)
			return ((result < 0) ?
					(int)((~((long)0)) >> 1) : (int)(~((~((long)0)) >> 1)));
	}
	return ((int)result);
}
