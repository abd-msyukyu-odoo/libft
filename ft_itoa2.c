/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 15:37:49 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/09 16:45:25 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_itoa_rec(long n, size_t count)
{
	char	*str;

	if (n < 10 && n > -10)
	{
		if (!(str = ft_strnew(count + ((n < 0) ? 1 : 0))))
			return (NULL);
		if (n < 0)
			str[count + 1] = '-';
	}
	else
		str = ft_itoa_rec(n / 10, count + 1);
	if (str != NULL)
		str[count] = ((n < 0) ? -1 : 1) * (n % 10) + '0';
	return (str);
}

static void		ft_strrev(char *str)
{
	size_t		len;
	size_t		i;
	char		tmp;

	len = ft_strlen(str);
	i = -1;
	while (--len > ++i)
	{
		tmp = str[i];
		str[i] = str[len];
		str[len] = tmp;
	}
}

char			*ft_itoa2(long n)
{
	return (ft_strrev(ft_itoa_rec(n, 0)));
}
