/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 16:22:56 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/19 15:47:44 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void		ft_swap_int(long *a, long *b)
{
	long	tmp;

	if (a == NULL || b == NULL)
		return ;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
