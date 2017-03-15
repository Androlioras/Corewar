#include "ft_joinf.h"

void	print_string(va_list va, char *new, size_t *j)
{
	size_t	i;
	char	*s;

	i = 0;
	s = va_arg(va, char*);
	while (s[i])
		new[(*j)++] = s[i++];
}

size_t	get_string_len(va_list va)
{
	return (ft_strlen(va_arg(va, char*)));
}
