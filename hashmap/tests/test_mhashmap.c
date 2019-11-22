#include "libft.h"
#include <stdio.h>

char			*in = "hivadeyfbcgopzwxklmjtunqsr";

typedef struct					s_named
{
	char						*key;
}								t_named;

int					display_mhmap_bnode_iteration(void *receiver, t_mhmap *source,
	int (*f)(void *receiver, void *sent))
{
	size_t			i;
	t_mbtree		*mbtree;
	int				out;

	i = 0;
	out = 1;
	while (out && i < source->hmap.array->size)
	{
		mbtree = (t_mbtree*)ft_array_get(source->hmap.array, i);
		if (mbtree->btree.root && mbtree->btree.root->rank)
		{
			printf("%zu \n", i);
			out = ft_btree_bnode_iteration(receiver, mbtree->btree.root, f);
		}
		++i;
	}
	return (out);
}

int				display_bnode(void *receiver, void *sent)
{
	t_named		*cur;

	cur = (t_named*)sent;
	if (receiver)
	{
		printf("%p :: %s\n", sent, cur->key);
		return (1);
	}
	return (0);
}

void			display_mhashmap(t_mhmap *m)
{
	display_mhmap_bnode_iteration(m, m, display_bnode);
	printf("n_items : %zu\nsize : %zu\n", m->hmap.array->n_items,
		m->hmap.array->size);
}

int				remove_bnode(void *receiver, void *sent)
{
	void		*rec;

	rec = ft_mbtree_remove((t_mbtree*)receiver, sent);
	printf("removing : %p || status : %p\n\n", sent,
		rec);
	printf("------------------------------\n\n");
	return (1);
}

void			remove_mhmap(t_mhmap *from)
{
	ft_mhmap_bnode_iteration(from, from, remove_bnode);
}

void			test_mhmap(void)
{
	t_memanager *mmng;
	t_named		*named;
	t_mhmap		*m;
	t_named		*saved;

	mmng = ft_memanager_construct_default();
	m = ft_mhmap_construct(mmng, 4, ft_hmap_hash_ascii);
	saved = NULL;
	for (int i = 0; i < 26; i++)
	{
		named = ft_memanager_get(mmng, sizeof(t_named));
		if (!saved)
			saved = named;
		named->key = &(in[i]);
		printf("added : %s || status : %d\n\n", named->key,
			ft_mhmap_add(m, named));
		printf("------------------------------\n\n");
	}
	display_mhmap(m);

	remove_mhmap(m);

	display_mhmap(m);

	printf("contains %s ? %d \n", saved->key, ft_mhmap_contains(m, saved));

	ft_mhmap_free(m);
	ft_memanager_free(mmng);
}