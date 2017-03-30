#include "../include/user.h"
#include "../include/instruct.h"

void	remp_param(t_utils *utils, t_env *env, char *line)
{
	int i;

	i = 0;
	if (line[i] == 'r')
	{
		utils->oct = (char)ft_atoi(&line[i + 1]);
		utils->verif = 1;
	}
	else if (line[i] == '%')
	{
		if (env->verif == 2)
		{
			utils->d_oct = ft_atoi(&line[i + 1]);
			utils->verif = 2;
		}
		else if (env->verif == 4)
		{
			utils->q_oct = (int)ft_atoi(&line[i + 1]);
			utils->verif = 3;
		}
	}
	// else
	// 	utils->d_oct = (short int)ft_atoi(line);
}

int		if_op_code(t_utils *utils, t_env *env)
{
	if (ft_strcmp(env->l_instr, "live") == 0 || ft_strcmp(env->l_instr, "zjmp") == 0 || 
		ft_strcmp(env->l_instr, "fork") == 0|| ft_strcmp(env->l_instr, "lfork") == 0)
		return (0);
	return (1);
}

int 	go_fast(char *line, int i)
{
	while (line[i] && line[i] != ' ' && line[i] != '	')
		i++;
	while (line[i] && (line[i] == ' ' || line[i] == '	'))
		i++;
	return (i);
}

char	get_op_code(t_utils *utils, t_env *env, char *str)
{
	char op;
	int i;
	op = 0;
	i = 0;
	op += (str[i] == 'r') ? 64 : 0;
	op += (str[i] == '%') ? 128 : 0;
	op += (ft_isdigit(str[i]) || str[i] == '-') ? 192 : 0;
	i = go_fast(str, i);
	op += (str[i] == 'r') ? 16 : 0;
	op += (str[i] == '%') ? 32 : 0;
	op += (ft_isdigit(str[i]) || str[i] == '-') ? 48 : 0;
	i = go_fast(str, i);
	op += (str[i] == 'r') ? 4 : 0;
	op += (str[i] == '%') ? 8 : 0;
	op += (ft_isdigit(str[i]) || str[i] == '-') ? 12 : 0;
	return (op);
}

t_utils		*create_new(t_utils *utils)
{
	int i;

	i = utils->test;
	utils->next = malloc(sizeof(t_utils));
	utils = utils->next;
	utils->test = i + 1;
	utils->label = NULL;
	utils->verif = 0;
	utils->oct = 0;
	utils->d_oct = 0;
	utils->q_oct = 0;
	utils->next = NULL;
	return (utils);
}


int		ft_strstr_u(char *meule, char *aigu, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (aigu[i] == '\0')
		return (0);
	while (meule[i] && meule[i] != c)
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
		{
			i = i - j;
			return (1);
		}
	}
	return (0);
}

unsigned char	ft_instr(char *line, t_env *env)
{
	unsigned char oct;
	
	oct = 0;
	oct = (ft_strstr_u(line, "live", ' ') == 1 && (env->l_instr = ft_strdup("live"))) ? LIVE : oct;
	oct = (ft_strstr_u(line, "ld", ' ') == 1 && (env->l_instr = ft_strdup("ld"))) ? LD : oct;
	oct = (ft_strstr_u(line, "st", ' ') == 1) && (env->l_instr = ft_strdup("st")) ? ST : oct;
	oct = (ft_strstr_u(line, "add", ' ') == 1) && (env->l_instr = ft_strdup("add")) ? ADD : oct;
	oct = (ft_strstr_u(line, "sub", ' ') == 1) && (env->l_instr = ft_strdup("sub")) ? SUB : oct;
	oct = (ft_strstr_u(line, "and", ' ') == 1) && (env->l_instr = ft_strdup("and")) ? AND : oct;
	oct = (ft_strstr_u(line, "or", ' ') == 1) && (env->l_instr = ft_strdup("or")) ? OR : oct;
	oct = (ft_strstr_u(line, "xor", ' ') == 1) && (env->l_instr = ft_strdup("xor")) ? XOR : oct;
	oct = (ft_strstr_u(line, "zjmp", ' ') == 1) && (env->l_instr = ft_strdup("zjmp")) ? ZJMP : oct;
	oct = (ft_strstr_u(line, "ldi", ' ') == 1) && (env->l_instr = ft_strdup("ldi")) ? LDI : oct;
	oct = (ft_strstr_u(line, "sti", ' ') == 1) && (env->l_instr = ft_strdup("sti")) ? STI : oct;
	oct = (ft_strstr_u(line, "fork", ' ') == 1) && (env->l_instr = ft_strdup("fork")) ? FORK : oct;
	oct = (ft_strstr_u(line, "lld", ' ') == 1) && (env->l_instr = ft_strdup("lld")) ? LLD : oct;
	oct = (ft_strstr_u(line, "lldi", ' ') == 1) && (env->l_instr = ft_strdup("lldi")) ? LLDI : oct;
	oct = (ft_strstr_u(line, "lfork", ' ') == 1) && (env->l_instr = ft_strdup("lfork")) ? LFORK : oct;
	oct = (ft_strstr_u(line, "aff", ' ') == 1) && (env->l_instr = ft_strdup("aff")) ? AFF : oct;
	return (oct);
}

char	*verif_label(char *line)
{
	int i;
	char *label;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '	')
		i++;
	if (line[i] && line[i - 1] == ':')
		label =(char *)malloc(sizeof(char) * i);
	else
		return (NULL);
	i = 0;
	while (line[i] && line[i] != ':')
	{
		label[i] = line[i];
		i++;
	}
	label[i] = '\0';
	return (label);
}

t_utils	*ft_recup_line(char *line, t_utils *utils, t_env *env)
{
	int i;

	i = 0;
	utils->label = verif_label(line);
	i = go_fast(line, i);
	utils->oct = ft_instr(&line[i], env);
	utils->verif = 1;
	ft_is_direct(env);
	i = go_fast(line, i);
	utils = create_new(utils);
	if (if_op_code(utils, env) == 1)
	{
		utils->oct = get_op_code(utils, env, &line[i]);
		utils->verif = 1;
		utils = create_new(utils);
	}
	while (line[i])
	{
		remp_param(utils, env, &line[i]);
		i = go_fast(line, i);
		utils = create_new(utils);
	}
	return (utils);
}

void	stock(char **tab, t_utils *utils, t_env *env)
{
	int i;

	i = 0;
	while (tab[i])
		utils = ft_recup_line(tab[i++], utils, env);
}

char 	*get_all(int fd)
{
	char	*str;
	char 	*line;

	str = NULL;
	line = NULL;
	while (get_next_line(fd, &line) == 1)
	{
		if (str == NULL)
		{
			str = ft_strdup(line);
			str = ft_strjoin_clean(str, "\n");
		}
		else if (line[0] && line[0] != '#' && line[0] != '\n')
		{
			str = ft_strjoin(str, line);
			str = ft_strjoin_clean(str, "\n");
		}
		free(line);
		line = NULL;
	}
	return (str);
}

t_utils		*ft_init_struct_utils(void)
{
	t_utils *utils;
	utils = malloc(sizeof(t_utils));
	utils->label = NULL;
	utils->verif = 0;
	utils->oct = 0;
	utils->d_oct = 0;
	utils->q_oct = 0;
	utils->test = 0;
	utils->next = NULL;
	return (utils);
}

t_env *ft_init_struct_env(void)
{
	t_env *env;
	env = malloc(sizeof(t_env));
	env->l_instr = NULL;
	return (env);
}

int	main(int argc, char **argv)
{
	 char *str;
	 int fd;
	 argc = 0;
	 t_utils *utils;
	 t_env *env;
	 utils = ft_init_struct_utils();
	 env = ft_init_struct_env();
	 str = get_all(open(argv[1], O_RDONLY));
	 stock(ft_strsplit(str, '\n'), utils, env);
	 fd = open("exemple.tor", O_CREAT | O_RDWR, 0777);
	 while (utils->next)
	 {
	 	if (utils->verif == 1)
	 		write(fd, &utils->oct, sizeof(char));
	 	else if (utils->verif == 2)
	 	{
	 		write (fd, 1 + (&utils->d_oct), 1);
	 		write (fd, &utils->d_oct, 1);
	 	}
	 	else if (utils->verif == 3)
		{
			write (fd, 3 + (&utils->q_oct), 1);
			write (fd, 2 + (&utils->q_oct), 1);
			write (fd, 1 + (&utils->q_oct), 1);
			write (fd, (&utils->q_oct), 1);
		}
	 printf("%d\n", utils->test);
	 printf("%s\n", utils->label);
	 printf("oct %hhu\n", utils->oct);
	 printf("2oct %hd\n", utils->d_oct);
	 printf("4oct %d\n", utils->q_oct);
	 utils = utils->next;
	 }

	return (0);	
}
