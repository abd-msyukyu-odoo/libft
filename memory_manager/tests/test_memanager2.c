#include <stdio.h>
#include "libft.h"

//display memarrays (each address and its size), for each block
//display imbrication of btree (address and size)

t_memanager		*test_memanager_construct(void)
{
	t_memanager	*mem;

	mem = ft_memanager_construct(3, 10, 100, 10);
	return (mem);
}

int				display_bnode_addr(void *receiver, void *sent)
{
	char		*padding;

	padding = (char*)receiver;
	printf("%s%p\n", padding, sent);
	return (1);
}

int				display_bnode_sthmap(void *receiver, void *sent)
{
	t_sthmap	*sthmap;
	static char *padding = "	";

	sthmap = (t_sthmap*)sent;
	if (receiver)
	{
		printf("---------sthmap---------\n");
		printf("%zu\n", sthmap->size.key);
		ft_hmap_bnode_iteration(padding, (t_hmap*)sthmap, display_bnode_addr);
	}
	return (1);
}

void			display_sthmap_tbt(t_btree *btree, int verbose)
{
	printf("_________btree display_________________________________\n");
	ft_btree_bnode_iteration((verbose) ? &verbose : NULL, btree->root,
		display_bnode_sthmap);
	return ;
}

int				contains_addr(t_memanager *memanager,
	void *addr, size_t size)
{
	t_sthmap	*sthmap;

	sthmap = (t_sthmap*)ft_btree_get((t_btree*)&memanager->sthmap_tbt, &size);
	if (!sthmap)
		return (0);
	return (ft_btree_contains((t_btree*)&sthmap->addr_thmap, addr));
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
	display_sthmap_tbt((t_btree*)&memanager->sthmap_tbt, verbose);
	display_memarrays(memanager, verbose);
	printf("\n=========end display===================================\n");
	return ;
}

void			fill_memanager(t_memanager *m)
{
	display_memanager(m, 1);
	char *a = ft_memanager_get(m, 2*sizeof(char));
	display_memanager(m, 1);
	char *b = ft_memanager_get(m, 3*sizeof(char));
	display_memanager(m, 1);
	char *c = ft_memanager_get(m, 4*sizeof(char));
	display_memanager(m, 1);
	char *d = ft_memanager_get(m, 5*sizeof(char));
	display_memanager(m, 1);
	char *e = ft_memanager_get(m, 6*sizeof(char));
	display_memanager(m, 1);
	size_t *sz = ft_memanager_get(m, sizeof(size_t));
	display_memanager(m, 1);
	int	*i = ft_memanager_get(m, sizeof(int));
	display_memanager(m, 1);
	ft_strcpy(a, "a");
	ft_strcpy(b, "ab");
	ft_strcpy(c, "abc");
	ft_strcpy(d, "abcd");
	ft_strcpy(e, "abcde");
	*sz = (size_t)-780565;
	*i = -153;
	void *big = ft_memanager_get(m, 1000);
	display_memanager(m, 1);
	///returning ptr
	printf("\n\nrefill\n\n");
	ft_memanager_refill(m, a);
	display_memanager(m, 1);
	ft_memanager_refill(m, b);
	display_memanager(m, 1);
	ft_memanager_refill(m, c);
	display_memanager(m, 1);
	ft_memanager_refill(m, big);
	display_memanager(m, 1);
	ft_memanager_refill(m, d);
	display_memanager(m, 1);
	ft_memanager_refill(m, e);
	display_memanager(m, 1);
	ft_memanager_refill(m, sz);
	display_memanager(m, 1);
	ft_memanager_refill(m, i);
	display_memanager(m, 1);
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
	fill_memanager(mem);
	printf("\n\ntry again\n\n");
	fill_memanager(mem);
	ft_memanager_free(mem);
}

int				main(void)
{
	printf("testing memanager\n");
	test_memanager();
	return (0);
}
