#include "libft.h"

int		ft_countchar(char *str, char c)
{
	int		i;

	i = 0;
	while (*str)
	{
		if (*str == c)
			i++;
		str++;
	}
	return (i);
}
