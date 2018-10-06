/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 17:19:11 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/06 17:30:50 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_isalpha(int c)
{
	return (c <= (int)((unsigned char)-1) && c > -1 &&
			(((unsigned char)c >= 'a' && (unsigned char)c <= 'z') ||
			((unsigned char)c >= 'A' && (unsigned char)c <= 'Z')));
}
