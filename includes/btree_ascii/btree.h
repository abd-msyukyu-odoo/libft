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
	struct s_bnode		*left;
	struct s_bnode		*right;
	struct s_bnode		*up;
	int					rank;
	t_memitem			*memitem;
}						t_bnode;

typedef struct			s_btree
{
	t_bnode				*root;
	int					(*cmp)(const char *s1, const char *s2);
	t_memanager			*mmng;
	t_memused			mused;
}						t_btree;

/*
** fill the empty btree, so it can be used
**
** @before: btree should be empty
**
** @param: btree : empty t_btree*
** @param: bnode_mmng : t_memanager* in charge of supplying t_bnode*
**
** @return: 1 : success
** @return: 0 : memory error
** @return: -1 : param error
*/
int						ft_btree_construct_extmem(t_btree *btree,
	t_memanager *bnode_mmng);

/*
** refill btree->mmng with t_bnode* stored within btree->mused
**
** @after: btree cannot be used anymore unless reconstructed
**
** @param: btree : to be destroyed t_btree*
*/
void					ft_btree_free_extmem(t_btree *btree);

/*
** get *t_named which has key
**
** @param: btree : to search in
** @param: key : to be searched for
**
** @return: t_named* which has key
** @return: NULL : btree does not contain key
*/
t_named					*ft_btree_get(t_btree *btree, char *key);

/*
** check if btree contains key
**
** @param: btree : to search in
** @param: key : to be searched for
**
** @return: 1 : btree does contain key
** @return: 0 : btree does not contain key
*/
int						ft_btree_contains(t_btree *btree, char *key);

/*
** add item to btree only if item->key is not already present
**
** @param: btree : to be modified
** @param: item : to be added
**
** @return: 1 : success
** @return: 0 : memory error
** @return: -1 : param error
** @return: -2 : error item->key is already present
*/
int						ft_btree_add(t_btree *btree, t_named *item);

/*
** replace item from btree only if item->key is already present
**
** @param: btree : to be modified
** @param: item : to be added
**
** @return: t_named* which was removed
** @return: NULL : error
*/
t_named					*ft_btree_replace(t_btree *btree, t_named *item);

/*
** remove item from btree if item->key is already present
**
** @param: btree : to be modified
** @param: key : to be searched for
**
** @return: t_named* which was removed
** @return: NULL : error
*/
t_named					*ft_btree_remove(t_btree *btree, char *key);

/*
** fill new with items from old
**
** @param: old : source
** @param: new : destination
**
** @return: 1 : success
** @return: 0 : memory error
** @return: -1 : param error
** return :
** 	1 : success
** 	-1 : btree was not modified
** 	0 : error
*/
int						ft_btree_fill_copy(t_btree *old, t_btree *new);

/*
** fill array with all items from btree
** return :
** 	1 : success
** 	-1 : array was not modified
** 	0 : error
*/
int						ft_btree_fill_array(t_btree *btree, t_array *array);

#endif
