#include "ft_printf.h"
#include <stdio.h>

int		main(void)
{
	size_t	i;

	i = 0;
	while (i < 10000000)
	{
		printf("%s\n", "test");
		i++;
	}
	return (0);
}