#include "libft.h"

void		ft_strclr(char *s)
{
	size_t		i;

	if (s == NULL)
		return ;
	i = -1;
	while (s[++i] != '\0')
		s[i] = '\0';
}
