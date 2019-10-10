#include <stdio.h>
#include "libft.h"

char		*aa = "aaaaa";
char		*bb = "bbbbb";
char		*cc = "ccccc";
char		*dd = "ddddd";
char		*ee = "eeeee";
char		*ff = "fffff";
char		*inside = "inside";
char		*start = "start";
char		*end = "end";

t_typemanager		*test_typemanager_construct()
{
	t_typemanager	*ma;

	ma = ft_typemanager_construct(3, sizeof(void*));
	return (ma);
}

void			display_typeused(t_typeused *mu)
{
	t_typeitem	*cur;

	cur = mu->typeitem;
	while (cur)
	{
		printf("	%s\n	%zu : i_typearray\n	%zu : n_used\n\n",
			*(char**)cur->item, cur->i_typearray, cur->n_used);
		if (cur == cur->next)
			break ;
		cur = cur->next;
	}
}

void			display_type_status(t_typemanager *ma, t_typeused mu[2])
{
	//display each element of each typeused from mu[]
	//display de availability of each typearray of ma
	unsigned int	i;

	printf("availability\n");
	i = 0;
	while (i < ma->typearrays->n_items)
	{
		printf("%d : %zu available\n", i,
			(*(t_typearray**)ft_array_get(ma->typearrays, i))->n_unused);
		i++;
	}
	printf("typeused 0\n");
	display_typeused(&mu[0]);
	printf("typeused 1\n");
	display_typeused(&mu[1]);
	printf("-------------------------------\n");
}

void			test_typemanager_get(t_typemanager *ma, t_typeused *mu)
{
	char		**rec;

	rec = (char**)ft_typemanager_get(ma, &mu[0]);
	*rec = aa;
	display_type_status(ma, mu);
	rec = (char**)ft_typemanager_get(ma, &mu[1]);
	*rec = bb;
	display_type_status(ma, mu);
	rec = (char**)ft_typemanager_get(ma, &mu[0]);
	*rec = cc;
	display_type_status(ma, mu);
	rec = (char**)ft_typemanager_get(ma, &mu[1]);
	*rec = dd;
	display_type_status(ma, mu);
	rec = (char**)ft_typemanager_get(ma, &mu[0]);
	*rec = ee;
	display_type_status(ma, mu);
	rec = (char**)ft_typemanager_get(ma, &mu[1]);
	*rec = ff;
	display_type_status(ma, mu);
}

void			test_typemanager_refill(t_typemanager *ma, t_typeused *mu)
{
	ft_typemanager_refill(ma, &mu[0]);
	display_type_status(ma, mu);
	ft_typemanager_refill(ma, &mu[1]);
	display_type_status(ma, mu);
}

void			test_typemanager_alternate(t_typemanager *ma, t_typeused *mu)
{
	char		**rec;

	rec = (char**)ft_typemanager_get(ma, &mu[0]);
	*rec = aa;
	rec = (char**)ft_typemanager_get(ma, &mu[1]);
	*rec = bb;
	rec = (char**)ft_typemanager_get(ma, &mu[0]);
	*rec = cc;
	rec = (char**)ft_typemanager_get(ma, &mu[1]);
	*rec = dd;
	rec = (char**)ft_typemanager_get(ma, &mu[0]);
	*rec = ee;
	display_type_status(ma, mu);
	ft_typemanager_refill(ma, &mu[0]);
	display_type_status(ma, mu);
	rec = (char**)ft_typemanager_get(ma, &mu[1]);
	*rec = ff;
	display_type_status(ma, mu);
	rec = (char**)ft_typemanager_get(ma, &mu[0]);
	*rec = aa;
	display_type_status(ma, mu);
	rec = (char**)ft_typemanager_get(ma, &mu[1]);
	*rec = cc;
	display_type_status(ma, mu);
	rec = (char**)ft_typemanager_get(ma, &mu[0]);
	*rec = ee;
	display_type_status(ma, mu);
}

void			test_typemanager()
{
	t_typemanager *ma;
	t_typeused mu[2];

	ft_typeused_initialize(&mu[0]);
	ft_typeused_initialize(&mu[1]);
	ma = test_typemanager_construct();
	if (!ma)
	{
		printf("construct error\n");
		return ;
	}
	printf("testing get\n");
	test_typemanager_get(ma, mu);
	printf("testing refill\n");
	test_typemanager_refill(ma, mu);
	printf("testing get and refill alternate\n");
	test_typemanager_alternate(ma, mu);
	ft_typemanager_free(ma);
}

int				main(void)
{
	printf("testing typemanager\n");
	test_typemanager();
	return (0);
}
