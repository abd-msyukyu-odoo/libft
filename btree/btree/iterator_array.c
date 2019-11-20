/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 19:00:31 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 19:00:33 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_array_add_typecast(void *receiver, void *sent)
{
	return (ft_array_add((t_array*)receiver, sent));
}

int					ft_btree_fill_array(t_btree *btree, t_array *array)
{
	return (ft_btree_bnode_iteration(array, btree->root,
		ft_array_add_typecast));
}
