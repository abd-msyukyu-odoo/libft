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
# define MMNG_DEFAULT_SIZE_COUNT	256
# define MMNG_DEFAULT_ADDR_COUNT	2048
# define MMNG_DEFAULT_CHUNK_SIZE	262144

typedef struct			s_key_stbtree
{
	size_t				key;
}						t_key_stbtree;

typedef struct			s_stbtree
{
	t_key_stbtree		size;
	t_tbtree			*addr_tbt;
	t_typeitem			*stbt_typeitem;
	t_typeitem			*tbt_typeitem;
}						t_stbtree;

typedef struct			s_memjump
{
	struct s_memjump	*next;
	struct s_memjump	*prev;
}						t_memjump;

typedef struct			s_memanager
{
	t_typeused			stbtree_used;
	t_typeused			tbtree_used;
	size_t				chunk_size;
	t_typemanager		*stbtree_mng;
	t_typemanager		*tbtree_mng;
	t_typemanager		*tbnode_mng;
	t_tbtree			*stbtree_tbt;
	t_array				*memarrays;
}						t_memanager;

int						ft_memanager_validate_amounts(size_t sizes,
	size_t addresses, size_t chunk_size);

void					ft_memanager_free(t_memanager *memanager);

t_array					*ft_memanager_extend_size(
	t_memanager *memanager, size_t chunk_size);

t_memanager				*ft_memanager_construct(size_t sizes, size_t addresses,
	size_t chunk_size);

t_memanager				*ft_memanager_construct_default(void);

void					*ft_memanager_get(t_memanager *memanager,
	size_t sizeof_item);

int						ft_memanager_refill(t_memanager *memanager, void *addr);

#endif
