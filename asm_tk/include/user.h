#ifndef USER_H
# define USER_H
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"
# define BUFF_SIZE 1024

typedef struct s_env
{
	char *l_instr;
	int verif;
}				t_env;

typedef struct s_utils
{
	int test;
	char *label;
	char *adr;
	int verif;
	unsigned char oct;
	short int d_oct;
	int 	q_oct;
	struct s_utils *next;
}				t_utils;

int		get_next_line(int const fd, char **line);
void 	ft_is_direct(t_env *env);
void	remp_type(char *str, t_env *env, t_utils *utils);

#endif
