#include "asm.h"

char *get_all(void)
{
	char	*str;
	char 	*line;

	line = NULL;
	while (get_next_line(fd, &line) == 1)
	{
		str = ft_strjoin_clean(line, str);
		free(line);
		line = NULL;
	}
}

int		main(int argc, char **argv)
{
	fd = open(argv[1], O_RDONLY);
	get_all();
	return (0);
}