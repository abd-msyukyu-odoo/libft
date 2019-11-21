/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:42:58 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 21:42:59 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_mhmap_bnode_iteration(void *receiver, t_mhmap *source,
	int (*f)(void *receiver, void *sent))
{
	size_t			i;
	t_mbtree		*mbtree;
	int				out;

	i = 0;
	out = 1;
	while (out && i < source->hmap.array->size)
	{
		mbtree = (t_mbtree*)ft_array_get(source->hmap.array, i);
		if (mbtree->btree.root && mbtree->btree.root->rank)
			out = ft_btree_bnode_iteration(receiver, mbtree->btree.root, f);
		++i;
	}
	return (out);
}
