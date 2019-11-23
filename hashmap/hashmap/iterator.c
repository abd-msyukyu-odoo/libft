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

int					ft_hmap_bnode_iteration(void *receiver, t_hmap *source,
	int (*f)(void *receiver, void *sent))
{
	size_t			i;
	t_btree			*btree;
	int				out;

	i = 0;
	out = 1;
	while (out && i < source->array->size)
	{
		btree = (t_btree*)ft_array_get(source->array, i);
		if (btree->root && btree->root->rank)
			out = ft_btree_bnode_iteration(receiver, btree->root, f);
		++i;
	}
	return (out);
}
