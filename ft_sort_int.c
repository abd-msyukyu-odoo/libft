/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 16:05:37 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/11 16:24:57 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_sort_int(long tab[], size_t s, size_t e)
{
	size_t		es;
	size_t		ee;
	size_t		sg;
	long		p;

	es = s;
	ee = s;
	sg = e;
	p = tab[s];
	while (ee < sg)
	{
		if (tab[ee] < p)
			ft_swap_int(tab + ee++, tab + es++);
		else if (tab[ee] == p)
			++ee;
		else
			ft_swap_int(tab + ee, tab + --sg);
	}
	if (s < es - 1)
		ft_sort_int(tab, s, es);
	if (sg < e - 1)
		ft_sort_int(tab, sg, e);
}
