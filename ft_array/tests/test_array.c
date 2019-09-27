#include "libft.h"
#include <stdio.h>

char		*aa = "aaaaa";
char		*bb = "bbbbb";
char		*cc = "ccccc";
char		*dd = "ddddd";
char		*ee = "eeeee";
char		*ff = "fffff";
char		*inside = "inside";
char		*start = "start";
char		*end = "end";

void			display_array(t_array *a)
{
	for (int i = 0; i < a->n_items; ++i)
	{
		printf("%s \n", *(char**)ft_array_get(a, i));
	}
	printf("n_items : %d\nsize : %d\n", a->n_items, a->size);
}

t_array			*test_construct_array()
{
	t_array		*a;

	a = ft_array_construct(0, sizeof(void*));
	return (a);
}

void			fill_array(t_array *a)
{
	ft_array_add(a, &aa);
	ft_array_add(a, &bb);
	ft_array_add(a, &cc);
	ft_array_add(a, &dd);
	ft_array_add(a, &ee);
	ft_array_add(a, &ff);
}

void			test_array_add(void)
{
	t_array		*a;

	a = test_construct_array();
	fill_array(a);
	display_array(a);
	ft_array_free(a);
}

void			test_array_insert(void)
{
	t_array		*a;

	a = test_construct_array();
	fill_array(a);
	ft_array_insert(a, 0, &start);
	ft_array_insert(a, 5, &inside);
	ft_array_insert(a, a->n_items, &end);
	display_array(a);
	ft_array_free(a);
}

void			test_array_remove(void)
{
	t_array		*a;
	t_array		*b;

	a = test_construct_array();
	b = ft_array_construct(0, a->sizeof_item);
	fill_array(a);
	ft_array_remove(a, a->n_items - 1, ft_array_inject(b));
	ft_array_remove(a, 3, ft_array_inject(b));
	ft_array_remove(a, 0, ft_array_inject(b));
	display_array(b);
	display_array(a);
	ft_array_free(a);
	ft_array_free(b);
}

void			test_array_index(void)
{
	t_array		*a;

	a = test_construct_array();
	fill_array(a);
	display_array(a);
	printf("first : %d\nthird : %d\nlast: %d\nfake : %d\n",
		ft_array_index(a, &aa),
		ft_array_index(a, &cc),
		ft_array_index(a, &ff),
		ft_array_index(a, NULL));
	ft_array_free(a);
}

int				main(void)
{
	printf("testing array\n");
	test_array_add();
	test_array_insert();
	test_array_remove();
	test_array_index();
	return (0);
}
