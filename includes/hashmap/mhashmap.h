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

#endif
