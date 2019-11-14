#include "libft.h"
#define CMP_MMNG_INSTANCES 800000
#define CMP_MMNG_SIZES 100

void			basic_memanager()
{
	t_memanager	*mng;
	char		*test[CMP_MMNG_INSTANCES];

	mng = ft_memanager_construct_default();
	for (int i = 0; i < CMP_MMNG_INSTANCES; i++)
	{
		test[i] = ft_memanager_get(mng, sizeof(char) * (1 + i % CMP_MMNG_SIZES));
	}
	for (int i = 0; i < CMP_MMNG_INSTANCES; i++)
	{
		ft_memanager_refill(mng, test[i]);
		test[i] = ft_memanager_get(mng, sizeof(char) * (CMP_MMNG_SIZES - i % CMP_MMNG_SIZES));
	}
	ft_memanager_free(mng);
}

int				main(void)
{
	basic_memanager();
	return (0);
}
