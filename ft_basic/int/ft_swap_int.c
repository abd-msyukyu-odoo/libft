/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 16:22:56 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/20 17:59:02 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basicft.h"

void		ft_swap_int(long *a, long *b)
{
	long	tmp;

	if (a == NULL || b == NULL)
		return ;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
