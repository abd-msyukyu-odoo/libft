#include "libft.h"

void		ft_striter.c(char *s, void (*f)(char *))
{
	size_t		i;

	i = -1;
	while (s[++i] != '\0')
		f(s + i);
}
