#include "libft.h"
#include <stdio.h>


char			*in = "hivadeyfbcgopzwxklmjtunqsr";

int				display_bnode_addr(void *receiver, void *sent)
{
	char		*padding;

	padding = (char*)receiver;
	printf("%s%p\n", padding, sent);
	return (1);
}

int				display_bnode_stbtree(void *receiver, void *sent)
{
	t_stbtree	*stbtree;
	static char *padding = "	";

	stbtree = (t_stbtree*)sent;
	if (receiver)
	{
		printf("---------stbtree---------\n");
		printf("%zu\n", stbtree->size.key);
		ft_btree_bnode_iteration(padding, stbtree->addr_tbt->btree.root,
			display_bnode_addr);
	}
	return (1);
}

void			display_stbtree_tbt(t_btree *btree, int verbose)
{
	printf("_________btree display_________________________________\n");
	ft_btree_bnode_iteration((verbose) ? &verbose : NULL, btree->root,
		display_bnode_stbtree);
	return ;
}

int				contains_addr(t_memanager *memanager,
	void *addr, size_t size)
{
	t_stbtree	*stbtree;

	stbtree = (t_stbtree*)ft_btree_get((t_btree*)memanager->stbtree_tbt, &size);
	if (!stbtree)
		return (0);
	return (ft_btree_contains((t_btree*)stbtree->addr_tbt, addr));
}

void			display_memarray(t_array *memarray, t_memanager *memanager,
	int verbose)
{
	t_memjump	*cur;
	void		*addr;
	size_t		size;

	cur = (t_memjump*)ft_array_get(memarray, sizeof(size_t));
	while (cur->next)
	{
		addr = (void*)((char*)cur + sizeof(t_memjump));
		size = (size_t)((char*)cur->next - (char*)addr);
		printf("	%p	%zu	%s\n", addr, size,
			(verbose && contains_addr(memanager, addr, size)) ? "free" : "");
		cur = cur->next;
	}
}

void			display_memarrays(t_memanager *memanager, int verbose)
{
	size_t		i;

	printf("_________memarrays display_____________________________\n");
	i = 0;
	while (i < memanager->memarrays->n_items)
	{
		printf("---------block-----------\n");
		printf("%zu\n", i);
		display_memarray(*(t_array**)ft_array_get(memanager->memarrays, i),
			memanager, verbose);
		i++;
	}
	return ;
}

void			display_memanager(t_memanager *memanager, int verbose)
{
	printf("\n=========memanager display=============================\n");
	display_stbtree_tbt((t_btree*)memanager->stbtree_tbt, verbose);
	display_memarrays(memanager, verbose);
	printf("\n=========end display===================================\n");
	return ;
}

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

void			display_mhmap(t_mhmap *m)
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

int				named_free(void *receiver, void *sent)
{
	if (!receiver)
	return (0);
	ft_memanager_refill((t_memanager*)receiver, *(t_named**)sent);
	return (1);
}

void			test_mhmap(void)
{
	t_memanager *mmng;
	t_named		*named;
	t_mhmap		*m;
	t_named		*saved;
	t_marray	*marray;

	mmng = ft_memanager_construct_default();
	m = ft_mhmap_construct(mmng, 4, ft_hmap_hash_ascii);
	marray = ft_marray_construct(mmng, 26, sizeof(void*));
	saved = NULL;
	for (int i = 0; i < 26; i++)
	{
		named = ft_memanager_get(mmng, sizeof(t_named));
		if (!saved)
			saved = named;
		named->key = &(in[i]);
		ft_marray_add(marray, &named);
		printf("added : %s || status : %d\n\n", named->key,
			ft_mhmap_add(m, named));
		printf("------------------------------\n\n");
	}
	display_mhmap(m);

	for (int i = 0; i < 26; i++)
	{
		named = *(t_named**)ft_array_get((t_array*)marray, i);
		printf("removing : %p || status : %d\n\n", named,
			ft_mhmap_remove(m, named));
		printf("------------------------------\n\n");
	}

	display_mhmap(m);

	printf("contains %s ? %d \n", saved->key, ft_mhmap_contains(m, saved));

	ft_array_iteration(marray->mmng, (t_array*)marray, named_free);

	ft_mhmap_free(m);
	ft_marray_free(marray);
	display_memanager(mmng, 1);
	ft_memanager_free(mmng);
}

int				main(void)
{
	test_mhmap();
	return (0);
}
