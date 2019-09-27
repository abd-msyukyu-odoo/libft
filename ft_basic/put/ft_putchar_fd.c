/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 11:47:20 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/20 17:39:47 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basicft.h"
#include <unistd.h>

void		ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
