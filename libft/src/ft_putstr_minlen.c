#include "libft.h"

void	ft_putstr_minlen(char *str, size_t len)
{
	if (str && len)
		write(1, str, len);
}
