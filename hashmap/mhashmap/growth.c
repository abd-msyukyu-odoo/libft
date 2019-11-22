/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   growth.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:42:58 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 21:42:59 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_mhmap_add(t_mhmap *mhmap, void *item)
{
	t_mbtree		*mbtree;

	if (!mhmap || !item)
		return (-1);
	mbtree = ft_mhmap_get(mhmap, item);
	if (!mbtree->mmng && !ft_mbtree_initialize(mbtree, mhmap->mmng,
		ft_btree_cmp_addr))
		return (0);
	return (ft_mbtree_add(mbtree, item));
}
