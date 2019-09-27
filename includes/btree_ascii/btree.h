/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:28:36 by dabeloos          #+#    #+#             */
/*   Updated: 2019/06/17 18:28:38 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_H
# define BTREE_H
# include <stdlib.h>
# include "btree_ascii/named.h"
# include "array/array.h"
# include "basic_functions/basicft.h"
# include "memory_manager/memanager.h"

typedef struct			s_bnode
{
	t_named				*named;
	struct s_btree		*left;
	struct s_btree		*right;
	struct s_btree		*up;
	unsigned int		rank;
}						t_bnode;

typedef struct			s_btree
{
	t_bnode				*root;
	int					(*cmp)(const char *s1, const char *s2);
	t_memanager			*mmng;
	t_memused			mused;
}						t_btree;

/*
** create a t_btree instance
** return :
** 	t_btree* : created instance
** 	NULL : error
*/
t_btree					*ft_btree_construct(t_named *named);

/*
** free the t_btree instance, but not the items
*/
void					ft_btree_free(t_btree *btree);

/*
** add item to the btree only if its key is not already present
** return :
** 	1 : success
** 	-1 : btree was not modified
** 	0 : error
*/
int						ft_btree_add(t_btree *btree, t_named *item);

/*
** get t_named item with key
** return :
** 	t_named* : item with key
** 	NULL : btree does not contains key
*/
t_named					*ft_btree_get_named(t_btree *btree, char *key);

/*
** replace item only if its key is already present
** return :
** 	t_named* : previous item with key
** 	NULL : btree does not contains key
*/
t_named					*ft_btree_replace(t_btree *btree, t_named *item);

/*
** check if btree contains key
** return :
** 	1 : btree contains key
** 	0 : btree does not contain key
*/
unsigned int			ft_btree_contains(t_btree *btree, char *key);

/*
** remove item with key from the btree
** return :
** 	t_named* : removed item
** 	NULL : btree does not contains key
*/
t_named					*ft_btree_remove(t_btree *btree, char *key);

/*
** fill new_btree with all items from old_btree
** return :
** 	1 : success
** 	-1 : btree was not modified
** 	0 : error
*/
int						ft_btree_fill_copy(t_btree *old_btree,
							t_btree *new_btree);

/*
** fill array with all items from btree
** return :
** 	1 : success
** 	-1 : array was not modified
** 	0 : error
*/
int						ft_btree_fill_array(t_btree *btree, t_array *array);

#endif
