/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mhashmap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 20:27:08 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 20:27:10 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MHASHMAP_H
# define MHASHMAP_H
# include "hashmap/hashmap.h"
# include "memory_manager/memanager.h"
# include "array/marray.h"
# include "btree/mbtree.h"

typedef struct			s_mhmap
{
	t_hmap				hmap;
	t_memanager			*mmng;
}						t_mhmap;

t_mhmap					*ft_mhmap_construct(t_memanager *mmng, size_t size,
	int (*hash)(void *s, size_t size));

void					ft_mhmap_free(t_mhmap *mhmap);

t_mbtree				*ft_mhmap_get(t_mhmap *mhmap, void *item);

int						ft_mhmap_contains(t_mhmap *mhmap, void *item);

int						ft_mhmap_add(t_mhmap *mhmap, void *item);

int						ft_mhmap_bnode_iteration(void *receiver, t_mhmap *source,
	int (*f)(void *receiver, void *sent));

#endif
