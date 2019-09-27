/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:26:10 by dabeloos          #+#    #+#             */
/*   Updated: 2019/06/17 18:26:12 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_btree_construct_extmem(t_btree *btree,
	t_memanager *bnode_mmng)
{
	if (!btree || !bnode_mmng)
		return (0);
	btree->mused = (t_memused){NULL, NULL};
	btree->root = (t_bnode*)ft_memanager_get(bnode_mmng, &btree->mused);
	if (!btree->root)
		return (0);
	btree->cmp = ft_strcmp;
	btree->mmng = bnode_mmng;
	return (1);
}

