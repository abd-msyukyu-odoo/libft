/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 12:49:56 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/10 12:49:58 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_itoa_rec(long n, size_t count)
{
	char	*str;

	if (n < 10 && n > -10)
	{
		if (!(str = ft_strnew(count + ((n < 0) ? 2 : 1))))
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

static char		*ft_strrev(char *str)
{
	size_t		len;
	size_t		i;
	char		tmp;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	i = -1;
	while (--len > ++i)
	{
		tmp = str[i];
		str[i] = str[len];
		str[len] = tmp;
	}
	return (str);
}

char			*ft_itoa2(long n)
{
	return (ft_strrev(ft_itoa_rec(n, 0)));
}
