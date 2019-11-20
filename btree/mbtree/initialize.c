/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 18:41:14 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 18:41:14 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_mbtree_initialize_leaf(t_bnode *leaf, t_bnode *parent)
{
	leaf->named = NULL;
	leaf->left = NULL;
	leaf->right = NULL;
	leaf->rank = 0;
	leaf->up = (t_bnode*)parent;
}
