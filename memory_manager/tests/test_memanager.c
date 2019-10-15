#include <stdio.h>
#include "libft.h"

//display memarrays (each address and its size), for each block
//display imbrication of btree (address and size)

t_memanager		*test_memanager_construct(void)
{
	t_memanager	*mem;

	mem = ft_memanager_construct(3, 10, 100);
	return (mem);
}

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
		printf("size : %zu\n", stbtree->size.key);
		ft_btree_bnode_iteration(padding, stbtree->addr_tbt->btree.root,
			display_bnode_addr);
	}
	return (1);
}

void			display_stbtree_tbt(t_btree *btree, int verbose)
{
	printf("--------btree display--------\n");
	ft_btree_bnode_iteration((verbose) ? &verbose : NULL, btree->root,
		display_bnode_stbtree);
	return ;
}

int				contains_addr(t_memanager *memanager,
	void *addr, size_t size)
{
	t_stbtree	*stbtree;

	stbtree = (t_stbtree*)ft_btree_get((t_btree*)memanager->stbtree_tbt, &size);
	return (ft_btree_contains((t_btree*)stbtree->addr_tbt, addr));
}

void			display_memarray(t_array *memarray, t_memanager *memanager,
	int verbose)
{
	t_memjump	*cur;
	void		*addr;
	size_t		size;

	cur = (t_memjump*)ft_array_get(memarray, sizeof(size_t));
	addr = (void*)((char*)cur + sizeof(t_memjump));
	while (cur->next)
	{
		size = (size_t)((char*)cur->next - (char*)cur);
		printf("	%p	size : %zu	%s\n", addr, size,
			(verbose && contains_addr(memanager, addr, size)) ? "free" : "");
		cur = cur->next;
	}
}

void			display_memarrays(t_memanager *memanager, int verbose)
{
	size_t		i;

	printf("--------memarrays display--------\n");
	i = 0;
	while (i < memanager->memarrays->n_items)
	{
		printf("---------block %zu---------\n", i);
		display_memarray(*(t_array**)ft_array_get(memanager->memarrays, i),
			memanager, verbose);
		i++;
	}
	return ;
}

void			display_memanager(t_memanager *memanager, int verbose)
{
	display_stbtree_tbt((t_btree*)memanager->stbtree_tbt, verbose);
	//display_memarrays(memanager, verbose);
	return ;
}

void			fill_memanager(t_memanager *m)
{
	char *a = ft_memanager_get(m, 2*sizeof(char));
	char *b = ft_memanager_get(m, 3*sizeof(char));
	char *c = ft_memanager_get(m, 4*sizeof(char));
	char *d = ft_memanager_get(m, 5*sizeof(char));
	char *e = ft_memanager_get(m, 6*sizeof(char));
	size_t *sz = ft_memanager_get(m, sizeof(size_t));
	int	*i = ft_memanager_get(m, sizeof(int));
	ft_strcpy(a, "a");
	ft_strcpy(b, "ab");
	ft_strcpy(c, "abc");
	ft_strcpy(d, "abcd");
	ft_strcpy(e, "abcde");
	*sz = (size_t)-780565;
	*i = -153;
}

void			test_memanager()
{
	t_memanager	*mem;

	mem = test_memanager_construct();
	if (!mem)
	{
		printf("construct error\n");
		return ;
	}
	//fill_memanager(mem);
	display_memanager(mem, 1);
	ft_memanager_free(mem);
}

int				main(void)
{
	printf("testing memanager\n");
	test_memanager();
	return (0);
}
