#include "../include/user.h"

void 	ft_is_direct(t_env *env)
{
	env->verif = 0;
	env->verif = (ft_strcmp(env->l_instr, "live") == 0) ? 4 : env->verif;	
	env->verif = (ft_strcmp(env->l_instr, "ld") == 0) ? 4 : env->verif;
	env->verif = (ft_strcmp(env->l_instr, "st") == 0) ? 0 : env->verif;
	env->verif = (ft_strcmp(env->l_instr, "add") == 0) ? 0 : env->verif;
	env->verif = (ft_strcmp(env->l_instr, "sub") == 0) ? 0 : env->verif;
	env->verif = (ft_strcmp(env->l_instr, "and") == 0) ? 4 : env->verif;
	env->verif = (ft_strcmp(env->l_instr, "or") == 0) ? 4 : env->verif;
	env->verif = (ft_strcmp(env->l_instr, "xor") == 0) ? 4 : env->verif;
	env->verif = (ft_strcmp(env->l_instr, "zjmp") == 0) ? 2 : env->verif;
	env->verif = (ft_strcmp(env->l_instr, "ldi") == 0) ? 2 : env->verif;
	env->verif = (ft_strcmp(env->l_instr, "sti") == 0) ? 2 : env->verif;
	env->verif = (ft_strcmp(env->l_instr, "fork") == 0) ? 2 : env->verif;
	env->verif = (ft_strcmp(env->l_instr, "lld") == 0) ? 4 : env->verif;
	env->verif = (ft_strcmp(env->l_instr, "lldi") == 0) ? 2 : env->verif;
	env->verif = (ft_strcmp(env->l_instr, "lfork") == 0) ? 2 : env->verif;
	env->verif = (ft_strcmp(env->l_instr, "aff") == 0) ? 0 : env->verif;
}

void	remp_type(char *str, t_env *env, t_utils *utils)
{
	int i;

	i = 0;
	if (str[i] == '%' && env->verif == 2)
	{
		utils->d_oct = 0;
		utils->verif = 2;
	}
	else if (str[i] == '%' && env->verif == 4)
	{
		utils->q_oct = 0;
		utils->verif = 3;
	}
}