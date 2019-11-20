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
	t_bnode			*bnode;

	mbtree = ft_mhmap_get(mhmap, item);
	if (!mbtree)
	{

	}
	bnode = ft_btree_get_bnode((t_btree*)mbtree, item);
}

// -> faire que mhmap get renvoie un pointeur de pointeur pour pouvoir modifier
//mbtree a distance sans devoir rechercher sa position