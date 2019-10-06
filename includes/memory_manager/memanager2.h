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

typedef struct          s_memjump
{
	void                *next;
	void                *previous;
}                       t_memjump;

typedef struct			s_memcache
{
	void				*cache[19];
	size_t				free;
	size_t				n_chunks;
}						t_memcache;

typedef struct          s_memarray
{
	t_array             *memory;
}                       t_memarray;

typedef struct          s_memanager
{
	t_array             *memarrays;
	unsigned int        i_available;
}                       t_memanager;

/*
** free the t_memarray instance and all its content
*/
void					ft_memarray_free(t_memarray *memarray);

/*
** free the t_memanager instance and all its content
*/
void					ft_memanager_free(t_memanager *memanager);

/*
** create a t_memarray instance
** return :
**  t_memarray* : created instance
**  NULL : memory error
*/
t_memarray				*ft_memarray_construct(size_t size);

t_memanager				*ft_memanager_construct(size_t memory);

int					    ft_memanager_extend_size(t_memanager *memanager,
	size_t memory_extension);

int						ft_memanager_refill(t_memanager *memanager);

void					*ft_memanager_get(t_memanager *memanager);

#endif