/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 20:09:45 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/08 12:03:48 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basicft.h"

char		*ft_strnew(size_t size)
{
	return ((char *)ft_memalloc(size + sizeof(char)));
}
