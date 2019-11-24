/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memanager.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:16:07 by dabeloos          #+#    #+#             */
/*   Updated: 2019/09/27 16:16:08 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMANAGER_H
# define MEMANAGER_H
# include <stdlib.h>
# include "array/array.h"
# include "memory_manager/typemanager.h"
# include "btree/tbtree.h"
# include "hashmap/thashmap.h"
# define MMNG_DEFAULT_SIZE_COUNT	32
# define MMNG_DEFAULT_ADDR_COUNT	2048
# define MMNG_DEFAULT_CHUNK_SIZE	262144
# define MMNG_DEFAULT_OVRLP_SIZE	1024

typedef struct			s_key_sthmap
{
	size_t				key;
}						t_key_sthmap;

typedef struct			s_sthmap
{
	t_key_sthmap		size;
	t_thmap				addr_thmap;
	t_typeitem			*sthm_typeitem;
	t_typeitem			*array_typeitem;
	t_typeitem			*items_typeitem;
}						t_sthmap;

typedef struct			s_memjump
{
	struct s_memjump	*next;
	struct s_memjump	*prev;
}						t_memjump;

typedef struct			s_memanager
{
	t_typeused			sthm_used;
	t_typeused			thm_used;
	t_typeused			array_used;
	t_typeused			items_used;
	t_tbtree			sthmap_tbt;
	size_t				chunk_size;
	size_t				overlap;
	t_typemanager		*sthm_mng;
	t_typemanager		*array_mng;
	t_typemanager		*items_mng;
	t_typemanager		*tbnode_mng;
	t_array				*memarrays;
}						t_memanager;

#endif
