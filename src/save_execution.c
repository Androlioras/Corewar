/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 14:47:47 by pribault          #+#    #+#             */
/*   Updated: 2017/05/14 20:33:34 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	(*g_func[17])(t_arena*, t_process*, t_uint([MAX_ARGS_NUMBER])) =
{
	NULL,
	&do_live,
	&do_ld,
	&do_st,
	&do_add,
	&do_sub,
	&do_and,
	&do_or,
	&do_xor,
	do_zjmp,
	&do_ldi,
	&do_sti,
	&do_fork,
	&do_lld,
	&do_lldi,
	&do_lfork,
	&do_aff
};

void	idx(t_uint *pc, t_uint n)
{
	if (n % MEM_SIZE > MEM_SIZE / 2)
		*pc = (*pc - (IDX_MOD - (n % IDX_MOD))) % MEM_SIZE;
	else
		*pc = (*pc + (n % IDX_MOD)) % MEM_SIZE;
}

t_char	verif_mask(t_uint mask, t_char f)
{
	t_char	res;
	t_char	n;
	t_char	i;

	i = 0;
	res = 1;
	if (!g_op[f].mask)
		return (1);
	while (i < g_op[f].n_params)
	{
		n = ((mask >> (-2 * i + 6)) & 3);
		if ((n == 1 && (g_op[f].params[i] & T_REG) != T_REG) ||
			(n == 2 && (g_op[f].params[i] & T_DIR) != T_DIR) ||
			(n == 3 && (g_op[f].params[i] & T_IND) != T_IND))
			res = 2;
		if (((g_op[f].params[i] & T_REG) == T_REG && (n & 1) == 1) ||
			((g_op[f].params[i] & T_DIR) == T_DIR && (n & 2) == 2) ||
			((g_op[f].params[i] & T_IND) == T_IND && n == 3))
			i++;
		else
			return (0);
	}
	return (res);
}

t_uint	get_mask(t_arena *arena, t_process *proc, t_char f)
{
	t_uint	mask;
	t_char	type;
	t_char	i;

	if (g_op[f].mask)
		return (get_number(arena, get_pc(proc->pc) + 1, 1));
	i = 0;
	mask = 0;
	while (i < g_op[f].n_params)
	{
		type = g_op[f].params[i];
		if (type == T_REG)
			mask += (1 << (6 - 2 * i));
		else if (type == T_DIR)
			mask += (2 << (6 - 2 * i));
		else if (type == T_IND)
			mask += (3 << (6 - 2 * i));
		i++;
	}
	return (mask);
}

t_uint	get_params(t_arena *ar, t_process *proc,
		t_uint (*p)[MAX_ARGS_NUMBER], t_char f)
{
	t_uint	mask;
	t_uint	pc;
	t_uint	l;
	t_char	i;

	mask = get_mask(ar, proc, f);
	pc = get_pc(proc->pc);
	l = (g_op[f].mask) ? 2 : 1;
	i = 0;
	while (i < g_op[f].n_params * 2)
	{
		if ((mask & (192 >> i)) == (64 >> i))
			(*p)[i / 2] = get_number(ar, pc + l, 1);
		else if ((mask & (192 >> i)) == (128 >> i))
			(*p)[i / 2] = get_number(ar, pc + l, 4 / (g_op[f].modif + 1));
		else if ((mask & (192 >> i)) == (192 >> i))
			(*p)[i / 2] = get_number(ar, pc + l, 2);
		else
			(*p)[i / 2] = 0;
		l += ((mask & (192 >> i)) == 64 >> i) ? 1 : 0;
		l += ((mask & (192 >> i)) == 192 >> i) ? 2 : 0;
		l += ((mask & (192 >> i)) == 128 >> i) ? 4 / (g_op[f].modif + 1) : 0;
		i += 2;
	}
	return (l);
}

void	call_function(t_arena *arena, t_process *process, t_char f)
{
	t_uint	p[MAX_ARGS_NUMBER];
	t_uint	mask;
	t_char	verif;
	t_uint	l;

	if (f > 16)
		move_process(arena, process, 1);
	mask = get_mask(arena, process, f - 1);
	verif = verif_mask(mask, f - 1);
	l = get_params(arena, process, &p, f - 1);
	if (arena->flags.flags & 2)
	{
		ft_printf("cycle %-6u ", arena->cycle);
		ft_printf("by %-4u  at %-5u %s (", process->id,
		get_pc(process->pc), g_op[f - 1].name);
		print_p(f - 1, mask, p);
		ft_printf(")\n");
	}
	if (verif == 1)
		g_func[f](arena, process, p);
	if (f != 9 && verif)
		move_process(arena, process, l);
	else if (verif == 0)
		move_process(arena, process, 1 + g_op[f - 1].mask);
}
