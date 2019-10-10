#include "libft.h"

typedef struct					s_named
{
	char						*key;
}								t_named;

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

int				display_bnode(void *receiver, void *sent)
{
	t_named		*cur;

	cur = (t_named*)sent;
	if (receiver)
	{
		ft_printf("%s\n", cur->key);
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

t_memanager		*memanager_construct_data()
{
	t_memanager	*ma;

	ma = ft_memanager_construct(26, sizeof(t_data));
	return (ma);
}

t_memanager		*memanager_construct_bnode()
{
	t_memanager *ma;

	ma = ft_memanager_construct(26, sizeof(t_bnode));
	return (ma);
}

t_memanager		*memanager_construct_btree()
{
	t_memanager *ma;

	ma = ft_memanager_construct(2, sizeof(t_btree));
	return (ma);
}

void			display_array(t_array *a)
{
	for (int i = 0; i < a->n_items; ++i)
	{
		ft_printf("%s \n", *(char**)ft_array_get(a, i));
	}
	ft_printf("n_items : %d\nsize : %d\n", a->n_items, a->size);
}

int				main(void)
{
	t_memanager *bnodes;
	t_memanager *datas;
	t_memanager *btrees;
	t_btree		*btree;
	t_btree		*copy;
	t_memused	mudatas;
	t_memused	mubtrees;
	t_data		*data;
	char		*key;

	bnodes = memanager_construct_bnode();
	datas = memanager_construct_data();
	btrees = memanager_construct_btree();
	ft_memused_initialize(&mudatas);
	ft_memused_initialize(&mubtrees);

	btree = ft_memanager_get(btrees, &mubtrees);
	ft_btree_construct_extmem(btree, bnodes, ft_btree_cmp_ascii);
	for (int i = 0; i < 26; i++)
	{
		data = ft_memanager_get(datas, &mudatas);
		data->named = (t_named){&(in[i])};
		data->ext = "ext";
		ft_printf("added : %s || status : %d\n\n", data->named.key,
			ft_btree_add(btree, (t_named*)data));
		ft_printf("------------------------------\n\n");
	}
	if (!btree)
		ft_printf("btree null\n");
	else
	{
		ft_printf("root %s\n", ((t_named*)btree->root->named)->key);
	}
	
	display_btree(btree, 1);

	copy = ft_memanager_get(btrees, &mubtrees);
	ft_btree_construct_extmem(copy, bnodes, ft_btree_cmp_ascii);
	ft_btree_fill_copy(btree, copy);

	ft_printf("\ncopy : \n\n");

	display_btree(copy, 1);

	t_array			*recipient;
	recipient = ft_array_construct(5, sizeof(t_data));
	ft_btree_fill_array(btree, recipient);

	ft_printf("\narray : \n\n");

	display_array(recipient);

	for (int i = 0; i < 26; i++)
	{
		key = &in[i];
		data = (t_data*)ft_btree_remove(btree, &key);
		ft_printf("removing : %s || status : %s\n\n", key,
			(!data) ? "(null)" : data->named.key);
		ft_printf("------------------------------\n\n");
	}

	display_btree(btree, 1);

	ft_array_free(recipient);
	ft_memanager_free(bnodes);
	ft_memanager_free(datas);
	ft_memanager_free(btrees);
	return (0);
}