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
	printf("n_items : %zu\nsize : %zu\n", a->n_items, a->size);
}

t_marray			*test_construct_marray(t_memanager *mmng)
{
	t_marray		*a;

	a = ft_marray_construct(mmng, 0, sizeof(void*));
	return (a);
}

void			fill_marray(t_marray *a)
{
	ft_marray_add(a, &aa);
	ft_marray_add(a, &bb);
	ft_marray_add(a, &cc);
	ft_marray_add(a, &dd);
	ft_marray_add(a, &ee);
	ft_marray_add(a, &ff);
}

void			test_marray_add(void)
{
	t_marray		*a;
	t_memanager 	*mmng;

	mmng = ft_memanager_construct_default();
	a = test_construct_marray(mmng);
	fill_marray(a);
	display_array((t_array*)a);
	ft_marray_free(a);
	ft_memanager_free(mmng);
}

void			test_marray_insert(void)
{
	t_marray		*a;
	t_memanager		*mmng;

	mmng = ft_memanager_construct_default();
	a = test_construct_marray(mmng);
	fill_marray(a);
	ft_marray_insert(a, 0, &start);
	ft_marray_insert(a, 5, &inside);
	ft_marray_insert(a, a->array.n_items, &end);
	display_array((t_array*)a);
	ft_marray_free(a);
	ft_memanager_free(mmng);
}

void			test_marray_remove(void)
{
	t_marray		*a;
	t_marray		*b;
	t_memanager		*mmng;

	mmng = ft_memanager_construct_default();
	a = test_construct_marray(mmng);
	b = ft_marray_construct(mmng, 0, a->array.sizeof_item);
	fill_marray(a);
	ft_array_remove((t_array*)a, a->array.n_items - 1, ft_marray_inject(b));
	ft_array_remove((t_array*)a, 3, ft_marray_inject(b));
	ft_array_remove((t_array*)a, 0, ft_marray_inject(b));
	display_array((t_array*)b);
	display_array((t_array*)a);
	ft_marray_free(a);
	ft_marray_free(b);
	ft_memanager_free(mmng);
}

void			test_marray_index(void)
{
	t_marray		*a;
	t_memanager	*mmng;

	mmng = ft_memanager_construct_default();
	a = test_construct_marray(mmng);
	fill_marray(a);
	display_array((t_array*)a);
	printf("first : %zu\nthird : %zu\nlast: %zu\nfake : %zu\n",
		ft_array_index((t_array*)a, &aa),
		ft_array_index((t_array*)a, &cc),
		ft_array_index((t_array*)a, &ff),
		ft_array_index((t_array*)a, NULL));
	ft_marray_free(a);
	ft_memanager_free(mmng);
}

int				main(void)
{
	printf("testing array\n");
	test_marray_add();
	test_marray_insert();
	test_marray_remove();
	test_marray_index();
	return (0);
}
