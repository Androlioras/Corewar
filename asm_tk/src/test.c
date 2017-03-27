#include "../include/user.h"
#include "../include/instruct.h"

t_utils		*create_new(t_utils *utils)
{
	utils->next = malloc(sizeof(t_utils));
	utils = utils->next;
	utils->label = NULL;
	utils->verif = 0;
	utils->oct = 0;
	utils->next = NULL;
	return (utils);
}

int 	go_fast(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '	')
		i++;
	while (line[i] && (line[i] == ' ' || line[i] == '	'))
		i++;
	return (i);
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

void	ft_recup_line(char *line, t_utils *utils, t_env *env)
{
	int i;

	i = 0;
	utils->label = verif_label(line);
	if (utils->label != NULL)
		i = go_fast(&line[i]);
	utils->oct = ft_instr(&line[i], env);

	ft_is_direct(env);
	printf("[%s]   [%d]\n", env->l_instr, env->verif);
	i = go_fast(&line[i]);
	utils = create_new(utils);
	if (line[i] == 'r')
	{
		i++;
		utils->oct = ft_atoi(line);
	}
	else
		remp_type(line, env, utils);
}

void	stock(char **tab, t_utils *utils, t_env *env)
{
	int i;

	i = 0;
	while (tab[i])
	{
		ft_recup_line(tab[i++], utils, env);
		utils = create_new(utils);
	}
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
	argc = 0;
	t_utils *utils;
	t_env *env;
	utils = ft_init_struct_utils();
	env = ft_init_struct_env();
	str = get_all(open(argv[1], O_RDONLY));
	stock(ft_strsplit(str, '\n'), utils, env);
	// while (utils->next)
	// {
	// 	printf("%s\n", utils->label);
	// 	printf("%hhu\n", utils->oct);
	// 	utils = utils->next;
	// }
	return (0);	
}