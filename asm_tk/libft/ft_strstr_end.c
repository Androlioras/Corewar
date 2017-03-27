#include "libft.h"

char	*ft_strstr_end(char *meule, char *aigu)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (aigu[i] == '\0')
		return (&meule[i]);
	while (meule[i])
	{
		if (aigu[j] == meule[i])
			j++;
		else
		{
			i = i - j;
			j = 0;
		}
		i++;
		if (aigu[j] == '\0')
			return (&meule[i]);
	}
	return (0);
}
