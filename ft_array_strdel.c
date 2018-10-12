/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_strdel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 14:40:43 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/12 15:16:04 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		ft_array_strdel(char ***arr)
{
	size_t		i;

	if (arr == NULL)
		return ;
	i = -1;
	while ((*arr)[++i] != NULL)
	{
		free((*arr)[i]);
	}
	free(*arr);
}
