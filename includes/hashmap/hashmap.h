/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 20:27:03 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 20:27:04 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHMAP_H
# define HASHMAP_H
# include <stdlib.h>
# include "basic_functions/basicft.h"
# include "array/array.h"
# include "btree/btree.h"

typedef struct			s_hmap
{
	t_array				*array;
	size_t				(*hash)(void *s, size_t size);
}						t_hmap;

size_t					ft_hmap_hash_ascii(void *s, size_t size);
size_t					ft_hmap_hash_addr(void *s, size_t size);
size_t					ft_hmap_hash_nbr(void *s, size_t size);

int						ft_hmap_bnode_iteration(void *receiver, t_hmap *source,
	int (*f)(void *receiver, void *sent));

t_btree					*ft_hmap_get(t_hmap *hmap, void *item);

int						ft_hmap_contains(t_hmap *hmap, void *item);

#endif
