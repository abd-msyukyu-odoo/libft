/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memused.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 19:26:40 by dabeloos          #+#    #+#             */
/*   Updated: 2019/09/29 19:26:41 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_memused_initialize(t_memused *memused)
{
	memused->memitem = NULL;
	memused->oldest = NULL;
	memused->recovery = NULL;
	memused->last = NULL;
}

void				ft_memused_recover(t_memused *memused, t_memitem *memitem)
{
	memitem->next_recovery = memused->recovery;
	memused->recovery = memitem;
}
