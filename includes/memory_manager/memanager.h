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

/*
** item : pointer to data
** next : pointer to next memitem
** next_oldest : cf oldest in t_memused
** i_memarray : index of the memarray which possess this memitem
** n_used : countdown of all contiguous memitems with the same memitems in
** 		a t_memused
*/
typedef struct			s_memitem
{
	void				*item;
	struct s_memitem	*next;
	struct s_memitem	*next_oldest;
	struct s_memitem	*next_recovery;
	unsigned int		i_memarray;
	unsigned int		n_used;
}						t_memitem;

/*
** memitem : LIFO pointers to used memitems
** oldest : Taken all contiguous memitems with the same i_memarray, the oldest
** 		one is an pointer of this LIFO (other elements are oldests with another
** 		i_memarray)
*/
typedef struct			s_memused
{
	t_memitem			*memitem;
	t_memitem			*oldest;
	t_memitem			*recovery;
	t_memitem			*last;
}						t_memused;

/*
** array : memory allocation for data
** memitems : memory allocation for memitems
** unused : LIFO pointers to unused memitems
** n_unused : length of unused
*/
typedef struct			s_memarray
{
	t_array				*array;
	t_array				*memitems;
	t_memitem			*unused;
	unsigned int		n_unused;
}						t_memarray;

/*
** memarrays : array of pointers to t_memarray
** i_available : smallest index in memarrays to t_memarray with n_unused > 0
*/
typedef struct			s_memanager
{
	t_array				*memarrays;
	unsigned int		i_available;
}						t_memanager;

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
t_memarray				*ft_memarray_construct(unsigned int size,
	size_t sizeof_item, unsigned int memindex);

/*
** create a t_memanager instance
** return :
**  t_memanager* : created instance
**  NULL : memory error
*/
t_memanager				*ft_memanager_construct(unsigned int size,
	size_t sizeof_item);

/*
** this function should not be used externaly unless in case of controlled
** high memory usage
** extend the number of elements that the memarray is able to store
** return :
**  1 : success
**  0 : memory error
*/
int						ft_memanager_extend_size(t_memanager *memanager,
	unsigned int new_size);

/*
** "free" the previously used items so that the memarray can provide them
** for ulterior usage without the need for actual free/malloc
** return :
**  void
*/
int						ft_memanager_refill(t_memanager *memanager,
	t_memused *used);

/*
** ask the memarray for a pointer to the stored data type. If none are
** available, double the size of the memarray.
** return :
**  void* : pointer to a fitting space for the data type handled by the memarray
*/
void					*ft_memanager_get(t_memanager *memanager,
	t_memused *used);

void					ft_memused_initialize(t_memused *memused);

#endif
