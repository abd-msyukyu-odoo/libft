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
	return (ft_btree_bnode_iteration(receiver, source->hash_btree->root, f));
}

int					ft_hmap_cell_identification(void *receiver, void *sent)
{
	t_hmap_wrapper	*wrapper;

	wrapper = (t_hmap_wrapper*)receiver;
	if (wrapper->equals(wrapper->item, sent))
	{
		wrapper->item = sent;
		return (0);
	}
	return (1);
}
