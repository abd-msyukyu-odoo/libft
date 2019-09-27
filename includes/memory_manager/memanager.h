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

typedef struct			s_memitem
{
	void				*item; // pointer to data
	struct s_memitem	*next; // pointer to next memitem
	struct s_memitem	*next_oldest;
	struct s_memitem	*next_newest;
	unsigned int		i_memarray;
	unsigned int		n_used;
}						t_memitem;

typedef struct			s_memused
{
	t_memitem			*memitem; // all used pointers to data
	t_memitem			*oldest; // first added used pointer with same index
	t_memitem			*newest; // last added used pointer with other index
}						t_memused;

typedef struct			s_memarray
{
	t_array				*array; // data
	t_array				*memitems; // pointers to data
	t_memitem			*unused; // all unused pointers to data
	unsigned int		n_unused; // amount of unused memitems
}						t_memarray;

typedef struct			s_memanager
{
	t_array				*memarrays;
	unsigned int		i_available;
	// todo better dispatching of available memory
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

#endif
