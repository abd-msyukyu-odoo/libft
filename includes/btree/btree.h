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
# include "array/array.h"
# include "basic_functions/basicft.h"
# include "memory_manager/typemanager.h"

/*
** named should be a pointer to a struct which respect the following :
** the first element should be of a type which differentiate it from others
** elements of the same type
*/
typedef struct			s_bnode
{
	void				*named;
	struct s_bnode		*left;
	struct s_bnode		*right;
	struct s_bnode		*up;
	int					rank;
	t_typeitem			*typeitem;
}						t_bnode;

/*
** cmp is a custom function which make use of the first element of
** t_bnode->named to sort the elements 
*/
typedef struct			s_btree
{
	t_bnode				*root;
	int					(*cmp)(void *s1, void *s2);
	t_typemanager		*tmng;
	t_typeused			tused;
}						t_btree;

/*
** fill the empty btree, so it can be used
**
** @before: btree should be empty
**
** @param: btree : empty t_btree*
** @param: bnode_mmng : t_typemanager* in charge of supplying t_bnode*
**
** @return: 1 : success
** @return: 0 : memory error
** @return: -1 : param error
*/
int						ft_btree_construct_extmem(t_btree *btree,
	t_typemanager *bnode_tmng, int (*cmp)(void *s1, void *s2));

/*
** refill btree->mmng with t_bnode* stored within btree->mused
**
** @after: btree cannot be used anymore unless reconstructed
**
** @param: btree : to be destroyed t_btree*
*/
void					ft_btree_free_extmem(t_btree *btree);

/*
** get object which has key
**
** @param: btree : to search in
** @param: key : to be searched for (pointer to type of t_bnode->named->"first")
**
** @return: objet which has key
** @return: NULL : btree does not contain key
*/
void					*ft_btree_get(t_btree *btree, void *key);

/*
** check if btree contains key
**
** @param: btree : to search in
** @param: key : to be searched for (pointer to type of t_bnode->named->"first")
**
** @return: 1 : btree does contain key
** @return: 0 : btree does not contain key
*/
int						ft_btree_contains(t_btree *btree, void *key);

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
int						ft_btree_add(t_btree *btree, void *item);

/*
** replace item from btree only if item->key is already present
**
** @param: btree : to be modified
** @param: item : to be added
**
** @return: object which was removed
** @return: NULL : error
*/
void					*ft_btree_replace(t_btree *btree, void *item);

/*
** remove item from btree if item->key is already present
**
** @param: btree : to be modified
** @param: key : to be searched for (pointer to type of t_bnode->named->"first")
**
** @return: object which was removed
** @return: NULL : error
*/
void					*ft_btree_remove(t_btree *btree, void *key);

/*
** apply f on each node starting from sent in sorted order, using receiver
** as the appliation tool
**
** @param: receiver : tool used in the process of f
** @param: sent : the current element from a t_btree*
** @param: f : the application function
**
** @return: 1 : success
** @return: 0 : memory error
** @return: -1 : error
*/
int						ft_btree_bnode_iteration(void *receiver, t_bnode *sent,
	int (*f)(void *receiver, void *sent));

/*
** fill new with items from old
**
** @param: old : source
** @param: new : destination
**
** @return: 1 : success
** @return: 0 : memory error
** @return: -1 : param error
*/
int						ft_btree_fill_copy(t_btree *old, t_btree *new_bt);

/*
** fill array with items from btree
**
** @param: btree : source
** @param: new : destination
**
** @return: 1 : success
** @return: 0 : memory error
** @return: -1 : param error
*/
int						ft_btree_fill_array(t_btree *btree, t_array *array);

int						ft_btree_cmp_ascii(void *s1, void *s2);
int						ft_btree_cmp_size(void *s1, void *s2);
int						ft_btree_cmp_addr(void *s1, void *s2);

/*
** internal functions
*/
int						ft_btree_construct_leaves(t_btree *btree,
	t_bnode *old_leaf);
t_bnode					*ft_btree_get_bnode(t_btree *btree, void *key);
t_bnode					*ft_btree_get_min_bnode(t_bnode *bnode);
t_bnode					**ft_btree_bnode_referent(t_btree *btree,
	t_bnode *bnode);
int						ft_bnode_sibling_spin(t_bnode *child,
	t_bnode **sibling);
void					ft_btree_rotate(t_btree *btree, t_bnode *bn, int spin);
int						ft_bnode_has_two_leaves(t_bnode *bnode);
void					ft_btree_rebalance_deleted(t_btree *btree, t_bnode *bn);

#endif
