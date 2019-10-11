#include "libft.h"
#include <stdio.h>

typedef struct					s_named
{
	char						*key;
}								t_named;

typedef struct					s_numbered
{
	size_t						key;
}								t_numbered;

typedef struct	s_test_n_btree
{
	t_numbered	numbered;
	void		*ext;
}				t_szdata;

typedef struct	s_test_btree
{
	t_named		named;
	void		*ext;
}				t_data;

char			*in = "hivadeyfbcgopzwxklmjtunqsr";
char			*order = "abcdefghijklmnopqrstuvwxyz";
char			*inorder = "zyxwvutsrqponmlkjihgfedcba";

char			*char_bnode(t_bnode *bn)
{
	if (!bn->rank)
		return ("(null)");
	else
		return (((t_named*)bn->named)->key);
}

size_t			size_t_bnode(t_bnode *bn)
{
	if (!bn->rank)
		return (777777);
	else
		return (((t_numbered*)bn->named)->key);
}

int				display_bnode(void *receiver, void *sent)
{
	t_named		*cur;

	cur = (t_named*)sent;
	if (receiver)
	{
		printf("%s\n", cur->key);
		return (1);
	}
	return (0);
}

int				display_szbnode(void *receiver, void *sent)
{
	t_numbered		*cur;

	cur = (t_numbered*)sent;
	if (receiver)
	{
		printf("%zu\n", cur->key);
		return (1);
	}
	return (0);
}

int				remove_bnode(void *receiver, void *sent)
{
	void		*rec;

	rec = ft_tbtree_remove((t_tbtree*)receiver, sent);
	printf("removing : %p || status : %p\n\n", sent,
		rec);
	printf("------------------------------\n\n");
	return (1);
}

void			remove_btree(t_btree *from, t_btree *to)
{
	ft_btree_bnode_iteration(to, from->root, remove_bnode);
}

int				display_pbnode(void *receiver, void *sent)
{
	t_numbered		*cur;

	cur = (t_numbered*)sent;
	if (receiver)
	{
		printf("%p\n", cur);
		return (1);
	}
	return (0);
}

void			display_btree(t_btree *b, int verbose)
{
	if (!b)
		return ;
	ft_btree_bnode_iteration((verbose) ? &verbose : NULL, b->root,
		display_bnode);
}

void			display_pbtree(t_btree *b, int verbose)
{
	if (!b)
		return ;
	ft_btree_bnode_iteration((verbose) ? &verbose : NULL, b->root,
		display_pbnode);
}

void			display_szbtree(t_btree *b, int verbose)
{
	if (!b)
		return ;
	ft_btree_bnode_iteration((verbose) ? &verbose : NULL, b->root,
		display_szbnode);
}

t_typemanager		*typemanager_construct_data()
{
	t_typemanager	*ma;

	ma = ft_typemanager_construct(26, sizeof(t_data));
	return (ma);
}

t_typemanager		*typemanager_construct_szdata()
{
	t_typemanager *ma;

	ma = ft_typemanager_construct(26, sizeof(t_szdata));
	return (ma);
}

t_typemanager		*typemanager_construct_tbnode()
{
	t_typemanager *ma;

	ma = ft_typemanager_construct(26, sizeof(t_tbnode));
	return (ma);
}

t_typemanager		*typemanager_construct_tbtree()
{
	t_typemanager *ma;

	ma = ft_typemanager_construct(2, sizeof(t_tbtree));
	return (ma);
}

void			display_array(t_array *a)
{
	for (int i = 0; i < a->n_items; ++i)
	{
		printf("%s \n", *(char**)ft_array_get(a, i));
	}
	printf("n_items : %d\nsize : %d\n", a->n_items, a->size);
}

void			display_szarray(t_array *a)
{
	for (int i = 0; i < a->n_items; ++i)
	{
		printf("%zu \n", *(size_t*)ft_array_get(a, i));
	}
	printf("n_items : %d\nsize : %d\n", a->n_items, a->size);
}

void			display_parray(t_array *a)
{
	for (int i = 0; i < a->n_items; ++i)
	{
		printf("%p \n", ft_array_get(a, i));
	}
	printf("n_items : %d\nsize : %d\n", a->n_items, a->size);
}

void			test_ptr_btree(void)
{
	t_typemanager *bnodes;
	t_typemanager *datas;
	t_typemanager *btrees;
	t_btree		*btree;
	t_btree		*copy;
	t_typeused	mudatas;
	t_typeused	mubtrees;
	t_szdata	*data;
	t_szdata	*data2;
	size_t		key;

	bnodes = typemanager_construct_tbnode();
	datas = typemanager_construct_szdata();
	btrees = typemanager_construct_tbtree();
	ft_typeused_initialize(&mudatas);
	ft_typeused_initialize(&mubtrees);

	btree = ft_typemanager_get(btrees, &mubtrees);
	ft_tbtree_construct((t_tbtree*)btree, bnodes, ft_btree_cmp_addr);
	for (int i = 0; i < 26; i++)
	{
		data = ft_typemanager_get(datas, &mudatas);
		data->numbered = (t_numbered){(size_t)((i % 7 + 2 * i) * (i % 3 + 4 * i) / (i % 5 + 1))};
		data->ext = "ext";
		printf("added : %p || status : %d\n\n", data,
			ft_tbtree_add((t_tbtree*)btree, (t_numbered*)data));
		printf("------------------------------\n\n");
	}
	if (!btree)
		printf("btree null\n");
	else
	{
		printf("root %p\n", btree->root->named);
	}
	
	display_pbtree(btree, 1);

	copy = ft_typemanager_get(btrees, &mubtrees);
	ft_tbtree_construct((t_tbtree*)copy, bnodes, ft_btree_cmp_addr);
	ft_btree_fill_tcopy(btree, (t_tbtree*)copy);

	printf("\ncopy : \n\n");

	display_pbtree(copy, 1);

	t_array			*recipient;
	recipient = ft_array_construct(5, sizeof(t_szdata));
	ft_btree_fill_array(btree, recipient);

	printf("\narray : \n\n");

	display_parray(recipient);

	remove_btree(copy, btree);

	display_pbtree(btree, 1);

	ft_array_free(recipient);
	ft_typemanager_free(bnodes);
	ft_typemanager_free(datas);
	ft_typemanager_free(btrees);
}

void			test_size_t_btree(void)
{
	t_typemanager *bnodes;
	t_typemanager *datas;
	t_typemanager *btrees;
	t_btree		*btree;
	t_btree		*copy;
	t_typeused	mudatas;
	t_typeused	mubtrees;
	t_szdata	*data;
	size_t		key;

	bnodes = typemanager_construct_tbnode();
	datas = typemanager_construct_szdata();
	btrees = typemanager_construct_tbtree();
	ft_typeused_initialize(&mudatas);
	ft_typeused_initialize(&mubtrees);

	btree = ft_typemanager_get(btrees, &mubtrees);
	ft_tbtree_construct((t_tbtree*)btree, bnodes, ft_btree_cmp_size);
	for (int i = 0; i < 26; i++)
	{
		data = ft_typemanager_get(datas, &mudatas);
		data->numbered = (t_numbered){(size_t)((i % 7 + 2 * i) * (i % 3 + 4 * i) / (i % 5 + 1))};
		data->ext = "ext";
		printf("added : %zu || status : %d\n\n", data->numbered.key,
			ft_tbtree_add((t_tbtree*)btree, (t_numbered*)data));
		printf("------------------------------\n\n");
	}
	if (!btree)
		printf("btree null\n");
	else
	{
		printf("root %zu\n", ((t_numbered*)btree->root->named)->key);
	}
	
	display_szbtree(btree, 1);

	copy = ft_typemanager_get(btrees, &mubtrees);
	ft_tbtree_construct((t_tbtree*)copy, bnodes, ft_btree_cmp_size);
	ft_btree_fill_tcopy(btree, (t_tbtree*)copy);

	printf("\ncopy : \n\n");

	display_szbtree(copy, 1);

	t_array			*recipient;
	recipient = ft_array_construct(5, sizeof(t_szdata));
	ft_btree_fill_array(btree, recipient);

	printf("\narray : \n\n");

	display_szarray(recipient);

	for (int i = 0; i < 26; i++)
	{
		key = (i % 7 + 2 * i) * (i % 3 + 4 * i) / (i % 5 + 1);
		data = (t_szdata*)ft_tbtree_remove((t_tbtree*)btree, &key);
		printf("removing : %zu || status : %zu\n\n", key,
			(!data) ? 777777 : data->numbered.key);
		printf("------------------------------\n\n");
	}

	display_szbtree(btree, 1);

	ft_array_free(recipient);
	ft_typemanager_free(bnodes);
	ft_typemanager_free(datas);
	ft_typemanager_free(btrees);
}

void			test_ascii_btree(void)
{
	t_typemanager *bnodes;
	t_typemanager *datas;
	t_typemanager *btrees;
	t_btree		*btree;
	t_btree		*copy;
	t_typeused	mudatas;
	t_typeused	mubtrees;
	t_data		*data;
	char		*key;

	bnodes = typemanager_construct_tbnode();
	datas = typemanager_construct_data();
	btrees = typemanager_construct_tbtree();
	ft_typeused_initialize(&mudatas);
	ft_typeused_initialize(&mubtrees);

	btree = ft_typemanager_get(btrees, &mubtrees);
	ft_tbtree_construct((t_tbtree*)btree, bnodes, ft_btree_cmp_ascii);
	for (int i = 0; i < 26; i++)
	{
		data = ft_typemanager_get(datas, &mudatas);
		data->named = (t_named){&(in[i])};
		data->ext = "ext";
		printf("added : %s || status : %d\n\n", data->named.key,
			ft_tbtree_add((t_tbtree*)btree, (t_named*)data));
		printf("------------------------------\n\n");
	}
	if (!btree)
		printf("btree null\n");
	else
	{
		printf("root %s\n", ((t_named*)btree->root->named)->key);
	}
	
	display_btree(btree, 1);

	copy = ft_typemanager_get(btrees, &mubtrees);
	ft_tbtree_construct((t_tbtree*)copy, bnodes, ft_btree_cmp_ascii);
	ft_btree_fill_tcopy(btree, (t_tbtree*)copy);

	printf("\ncopy : \n\n");

	display_btree(copy, 1);

	t_array			*recipient;
	recipient = ft_array_construct(5, sizeof(t_data));
	ft_btree_fill_array(btree, recipient);

	printf("\narray : \n\n");

	display_array(recipient);

	for (int i = 0; i < 26; i++)
	{
		key = &in[i];
		data = (t_data*)ft_tbtree_remove((t_tbtree*)btree, &key);
		printf("removing : %s || status : %s\n\n", key,
			(!data) ? "(null)" : data->named.key);
		printf("------------------------------\n\n");
	}

	display_btree(btree, 1);

	ft_array_free(recipient);
	ft_typemanager_free(bnodes);
	ft_typemanager_free(datas);
	ft_typemanager_free(btrees);
}

int				main(void)
{
	test_ascii_btree();
	test_size_t_btree();
	test_ptr_btree();
	return (0);
}