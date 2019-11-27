#include "libft.h"
#include <stdio.h>
#include <time.h>
#define CMP_MMNG_INSTANCES 2000000
#define CMP_MMNG_SIZES 100

clock_t		begin;
clock_t		end;

void			basic_malloc()
{
	char		**test;
	double		sum;

	test = malloc(sizeof(char*) * (CMP_MMNG_INSTANCES));
	printf("malloc :\n");
	sum = 0;
	for (int i = 0; i < CMP_MMNG_INSTANCES; i++)
	{
		begin = clock();
		test[i] = malloc(sizeof(char) * (1 + i % CMP_MMNG_SIZES));
		end = clock();
		sum += (double)(end - begin);
	}
	for (int i = 0; i < CMP_MMNG_INSTANCES; i++)
	{
		begin = clock();
		free(test[i]);
		test[i] = malloc(sizeof(char) * (CMP_MMNG_SIZES - i % CMP_MMNG_SIZES));
		end = clock();
		sum += (double)(end - begin);
	}
	printf("malloc(s) : %f\n", sum / CLOCKS_PER_SEC);
	begin = clock();
	for (int i = 0; i < CMP_MMNG_INSTANCES; i++)
		free(test[i]);
	end = clock();
	printf("free(s) : %f\n", (double)(end - begin) / CLOCKS_PER_SEC);
	free(test);
}

void			basic_memanager()
{
	t_memanager	*mng;
	char		**test;
	double		sum;
	double		sum_refill;

	test = malloc(sizeof(char*) * (CMP_MMNG_INSTANCES));
	printf("memanager :\n");
	begin = clock();
	mng = ft_memanager_construct_default();
	end = clock();
	sum = (double)(end - begin);
	printf("time init : %f\n", sum / CLOCKS_PER_SEC);
	sum_refill = 0;
	for (int i = 0; i < CMP_MMNG_INSTANCES; i++)
	{
		begin = clock();
		test[i] = ft_memanager_get(mng, sizeof(char) * (1 + i % CMP_MMNG_SIZES));
		end = clock();
		sum += (double)(end - begin);
	}
	for (int i = 0; i < CMP_MMNG_INSTANCES; i++)
	{
		begin = clock();
		ft_memanager_refill(mng, test[i]);
		end = clock();
		sum_refill += (double)(end - begin);
		sum += (double)(end - begin);
		begin = clock();
		test[i] = ft_memanager_get(mng, sizeof(char) * (CMP_MMNG_SIZES - i % CMP_MMNG_SIZES));
		end = clock();
		sum += (double)(end - begin);
	}
	printf("refill : %f\n", sum_refill / CLOCKS_PER_SEC);
	printf("malloc(s) : %f\n", sum / CLOCKS_PER_SEC);
	begin = clock();
	ft_memanager_free(mng);
	end = clock();
	printf("free(s) : %f\n", (double)(end - begin) / CLOCKS_PER_SEC);
	free(test);
}

void			basic_test()
{
	printf("\n\nbasic test (%d mallocs range(1,%d) + free\n\n", CMP_MMNG_INSTANCES, CMP_MMNG_SIZES);
	basic_memanager();
	basic_malloc();
}

int				main(void)
{
	basic_test();
	return (0);
}
