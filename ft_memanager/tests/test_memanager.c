#include "array.h"
#include "stdio.h"
#include "memarray.h"

/*
make -C ../libft re
make -C ../libft clean
gcc -g -fsanitize=address -o test test_array.c ../sources/array.c ../sources/memarray.c -I../includes -I../libft -L../libft/ -lft 
*/
// -g -fsanitize=address
char		*aa = "aaaaa";
char		*bb = "bbbbb";
char		*cc = "ccccc";
char		*dd = "ddddd";
char		*ee = "eeeee";
char		*ff = "fffff";
char		*inside = "inside";
char		*start = "start";
char		*end = "end";

t_memanager		*test_memanager_construct()
{
	t_memanager	*ma;

	ma = ft_memanager_construct(3, sizeof(void*));
	return (ma);
}

void			display_memused(t_memused *mu)
{
	t_memitem	*cur;

	cur = mu->memitem;
	while (cur)
	{
		printf("	%s\n	%u : i_memarray\n	%u : n_used\n\n",
			*(char**)cur->item, cur->i_memarray, cur->n_used);
		if (cur == cur->next)
			break ;
		cur = cur->next;
	}
}

void			display_mem_status(t_memanager *ma, t_memused mu[2])
{
	//display each element of each memused from mu[]
	//display de availability of each memarray of ma
	unsigned int	i;

	printf("availability\n");
	i = 0;
	while (i < ma->memarrays->n_items)
	{
		printf("%d : %u available\n", i,
			(*(t_memarray**)ft_array_get(ma->memarrays, i))->n_unused);
		i++;
	}
	printf("memused 0\n");
	display_memused(&mu[0]);
	printf("memused 1\n");
	display_memused(&mu[1]);
}

void			test_memanager_get(t_memanager *ma, t_memused *mu)
{
	char		**rec;

	rec = (char**)ft_memanager_get(ma, &mu[0]);
	*rec = aa;
	display_mem_status(ma, mu);
	rec = (char**)ft_memanager_get(ma, &mu[1]);
	*rec = bb;
	display_mem_status(ma, mu);
	rec = (char**)ft_memanager_get(ma, &mu[0]);
	*rec = cc;
	display_mem_status(ma, mu);
	rec = (char**)ft_memanager_get(ma, &mu[1]);
	*rec = dd;
	display_mem_status(ma, mu);
	rec = (char**)ft_memanager_get(ma, &mu[0]);
	*rec = ee;
	display_mem_status(ma, mu);
	rec = (char**)ft_memanager_get(ma, &mu[1]);
	*rec = ff;
	display_mem_status(ma, mu);
}

void			test_memanager_refill(t_memanager *ma, t_memused *mu)
{
	ft_memanager_refill(ma, &mu[0]);
	display_mem_status(ma, mu);
	ft_memanager_refill(ma, &mu[1]);
	display_mem_status(ma, mu);
}

void			test_memanager_alternate(t_memanager *ma, t_memused *mu)
{
	char		**rec;

	rec = (char**)ft_memanager_get(ma, &mu[0]);
	*rec = aa;
	rec = (char**)ft_memanager_get(ma, &mu[1]);
	*rec = bb;
	rec = (char**)ft_memanager_get(ma, &mu[0]);
	*rec = cc;
	rec = (char**)ft_memanager_get(ma, &mu[1]);
	*rec = dd;
	rec = (char**)ft_memanager_get(ma, &mu[0]);
	*rec = ee;
	display_mem_status(ma, mu);
	ft_memanager_refill(ma, &mu[0]);
	display_mem_status(ma, mu);
	rec = (char**)ft_memanager_get(ma, &mu[1]);
	*rec = ff;
	display_mem_status(ma, mu);
	rec = (char**)ft_memanager_get(ma, &mu[0]);
	*rec = aa;
	display_mem_status(ma, mu);
	rec = (char**)ft_memanager_get(ma, &mu[1]);
	*rec = cc;
	display_mem_status(ma, mu);
	rec = (char**)ft_memanager_get(ma, &mu[0]);
	*rec = ee;
	display_mem_status(ma, mu);
}

void			test_memanager()
{
	t_memanager *ma;
	t_memused mu[2];

	mu[0] = (t_memused){NULL, NULL, NULL};
	mu[1] = (t_memused){NULL, NULL, NULL};
	ma = test_memanager_construct();
	if (!ma)
	{
		printf("construct error\n");
		return ;
	}
	printf("testing get\n");
	test_memanager_get(ma, mu);
	printf("testing refill\n");
	test_memanager_refill(ma, mu);
	printf("testing get and refill alternate\n");
	test_memanager_alternate(ma, mu);
	ft_memanager_free(ma);
}

int				main(void)
{
	printf("testing memanager\n");
	test_memanager();
	return (0);
}
