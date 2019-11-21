/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shrink.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:43:07 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 21:43:08 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_mhmap_remove(t_mhmap *mhmap, void *item)
{
	t_mbtree		*mbtree;

	mbtree = ft_mhmap_get(mhmap, item);
	if (!mbtree->mmng)
		return (0);
	return ((ft_mbtree_remove(mbtree, item)) ? 1 : 0);
}
