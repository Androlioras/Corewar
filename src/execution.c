/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 14:47:47 by pribault          #+#    #+#             */
/*   Updated: 2017/03/30 14:44:55 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	idx(t_uint *pc, t_uint n)
{
	if (n % MEM_SIZE > MEM_SIZE / 2)
		*pc -= (IDX_MOD - (n % IDX_MOD));
	else
		*pc += (n % IDX_MOD);
}

t_char	verif_mask(t_uint mask, t_char f)
{
	t_char	n;
	t_char	i;

	i = 0;
	while (i < g_op[f].n_params)
	{
		n = ((mask >> (-2 * i + 6)) & 3);
		if ((n & 3) == 1 && (g_op[f].params[i] & T_REG) != T_REG)
			return (0);
		else if ((n & 3) == 2 && (g_op[f].params[i] & T_DIR) != T_DIR)
			return (0);
		else if ((n & 3) == 3 && (g_op[f].params[i] & T_IND) != T_IND)
			return (0);
		i++;
	}
	return (1);
}

t_uint	get_params(t_arena *ar, t_uint (*p)[MAX_ARGS_NUMBER], t_uint pc,
					t_char f)
{
	t_uint	mask;
	t_uint	l;
	t_char	i;

	mask = 1;
	if (f != 11 && f != 14 && f != 8 && f != 0)
		mask = get_number(ar, pc + 1, 1);
	l = (mask != 1) ? 2 : 1;
	i = 0;
	while (i < g_op[f].n_params * 2)
	{
		if ((mask & (192 >> i)) == (64 >> i))
			(*p)[i / 2] = get_number(ar, pc + l, 1);
		else if ((mask & (192 >> i)) == (128 >> i))
			(*p)[i / 2] = get_number(ar, pc + l, 4 / (g_op[f].modif + 1));
		else if ((mask & (192 >> i)) == (192 >> i))
			(*p)[i / 2] = get_number(ar, pc + l, 2);
		l += ((mask & (192 >> i)) == 64 >> i) ? 1 : 0;
		l += ((mask & (192 >> i)) == 192 >> i) ? 2 : 0;
		l += ((mask & (192 >> i)) == 128 >> i) ? 4 / (g_op[f].modif + 1) : 0;
		i += 2;
	}
	return (l);
}

void	call_function_2(t_arena *arena, t_process *process, t_char f)
{
	if (f == 11)
		do_sti(arena, process);
	else if (f == 12)
		do_fork(arena, process);
	else if (f == 13)
		do_lld(arena, process);
	else if (f == 14)
		do_lldi(arena, process);
	else if (f == 15)
		do_lfork(arena, process);
	else if (f == 16)
		do_aff(arena, process);
}

void	call_function(t_arena *arena, t_process *process, t_char f)
{
	if (arena->flags.flags & 2)
		ft_printf("%u %s\n", get_pc(process->pc), g_op[f - 1].name);
	if (f == 1)
		do_live(arena, process);
	else if (f == 2)
		do_ld(arena, process);
	else if (f == 3)
		do_st(arena, process);
	else if (f == 4)
		do_add(arena, process);
	else if (f == 5)
		do_sub(arena, process);
	else if (f == 6)
		do_and(arena, process);
	else if (f == 7)
		do_or(arena, process);
	else if (f == 8)
		do_xor(arena, process);
	else if (f == 9)
		do_zjmp(arena, process);
	else if (f == 10)
		do_ldi(arena, process);
	else
		call_function_2(arena, process, f);
}
