/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ardanel <ardanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 14:47:47 by pribault          #+#    #+#             */
/*   Updated: 2017/03/22 21:24:45 by ardanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

size_t	get_reg(t_process *process, t_char n, t_char *i)
{
	if (i)
		(*i)++;
	return (get_pc(process->reg[(n - 1) % REG_NUMBER]));
}

t_char	verif_mask(size_t mask, t_char f)
{
	t_char	n;
	t_char	i;

	i = 0;
	while (i < g_op[f].n_params)
	{
		n = ((mask & (0xc0 >> (2 * i))) >> (-2 * i + 6));
		if ((n & 1) && !(g_op[f].params[i] & T_REG))
			return (0);
		else if ((n & 2) && !(g_op[f].params[i] & T_DIR))
			return (0);
		else if ((n & 3) && !(g_op[f].params[i] & T_IND))
			return (0);
		i++;
	}
	return (1);
}

size_t	get_params(t_arena *ar, size_t (*p)[MAX_ARGS_NUMBER], size_t pc,
					t_char f)
{
	size_t	mask;
	size_t	l;
	t_char	i;

	mask = 1;
	if (f != 11 && f != 14 && f != 8 && f != 0)
		mask = get_number(ar, pc + 1, 1);
	if (!(verif_mask(mask, f)))
		return (0);
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

void	print_in_map(t_char arena[MEM_SIZE], size_t pc, t_char *n, t_char l)
{
	size_t	i;

	i = 0;
	while (i < l)
	{
		arena[(pc + i) % MEM_SIZE] = n[i];
		i++;
	}
}

void	do_live(t_arena *arena, t_process *process)
{
	size_t	id;
	t_char	i;

	id = get_number(arena, get_pc(process->pc) + 1, 4);
	i = 0;
	while (i < arena->n)
	{
		if (arena->champs[i].id == id)
		{
			ft_printf("un processus dit que le joueur %d(%s) est en vie\n",
			i + 1, arena->champs[i].name);
			arena->champs[i].live++;
		}
		i++;
	}
	move_process(process, 5);
}

void	do_ld(t_arena *arena, t_process *proc)
{
	size_t	p[MAX_ARGS_NUMBER];
	size_t	mask;
	size_t	l;

	l = get_params(arena, &p, get_pc(proc->pc), 1);
	mask = get_number(arena, get_pc(proc->pc) + 1, 1);
	if (((mask & 0xc0) >> 6) == 3)
		p[0] = get_number(arena, p[0], 4);
	ft_memcpy(proc->reg[(p[1] - 1) % REG_NUMBER], &p, REG_SIZE);
	move_process(proc, l);
	proc->carry = 1;
}

void	do_st(t_arena *arena, t_process *process)
{
	size_t	params[MAX_ARGS_NUMBER];
	size_t	mask;
	size_t	l;

	l = get_params(arena, &params, get_pc(process->pc), 2);
	mask = get_number(arena, get_pc(process->pc) + 1, 1);

	move_process(process, l);
}

void	do_add(t_arena *arena, t_process *process)
{
	size_t	params[MAX_ARGS_NUMBER];
	size_t	res;
	size_t	l;

	l = get_params(arena, &params, get_pc(process->pc), 3);
	res = ft_endian(get_pc(process->reg[(params[0] - 1) % REG_NUMBER]));
	res += ft_endian(get_pc(process->reg[(params[1] - 1) % REG_NUMBER]));
	ft_endian_c((t_char*)&res);
	ft_memcpy(process->reg[(params[2] - 1) % REG_NUMBER], &res, REG_SIZE);
	move_process(process, l);
	process->carry = 1;
}

void	do_sub(t_arena *arena, t_process *process)
{
	size_t	params[MAX_ARGS_NUMBER];
	size_t	res;
	size_t	l;

	l = get_params(arena, &params, get_pc(process->pc), 3);
	res = ft_endian(get_pc(process->reg[(params[0] - 1) % REG_NUMBER]));
	res -= ft_endian(get_pc(process->reg[(params[1] - 1) % REG_NUMBER]));
	ft_endian_c((t_char*)&res);
	ft_memcpy(process->reg[(params[2] - 1) % REG_NUMBER], &res, REG_SIZE);
	process->carry = 1;
	move_process(process, l);
}

void	do_and(t_arena *arena, t_process *proc)
{
	size_t	p[MAX_ARGS_NUMBER];
	size_t	mask;
	size_t	l;

	l = get_params(arena, &p, get_pc(proc->pc), 5);
	mask = get_number(arena, get_pc(proc->pc) + 1, 1);
	if (((mask & 0xc0) >> 6) == 1)
		ft_memcpy(p, proc->reg[(p[0] - 1) % REG_NUMBER], REG_SIZE);
	else if (((mask & 0xc0) >> 6) == 3)
		p[0] = get_number(arena, p[0], 4);
	if (((mask & 0x30) >> 4) == 1)
		ft_memcpy(p + 1, proc->reg[(p[1] - 1) % REG_NUMBER], REG_SIZE);
	else if (((mask & 0x30) >> 4) == 3)
		p[1] = get_number(arena, p[1], 4);
	mask = (p[0] & p[1]);
	ft_memcpy(proc->reg[(p[2] - 1) % REG_NUMBER], &mask, REG_SIZE);
	move_process(proc, l);
	proc->carry = 1;
}

void	do_or(t_arena *arena, t_process *proc)
{
	size_t	p[MAX_ARGS_NUMBER];
	size_t	mask;
	size_t	l;

	l = get_params(arena, &p, get_pc(proc->pc), 5);
	mask = get_number(arena, get_pc(proc->pc) + 1, 1);
	if (((mask & 0xc0) >> 6) == 1)
		ft_memcpy(p, proc->reg[(p[0] - 1) % REG_NUMBER], REG_SIZE);
	else if (((mask & 0xc0) >> 6) == 3)
		p[0] = get_number(arena, p[0], 4);
	if (((mask & 0x30) >> 4) == 1)
		ft_memcpy(p + 1, proc->reg[(p[1] - 1) % REG_NUMBER], REG_SIZE);
	else if (((mask & 0x30) >> 4) == 3)
		p[1] = get_number(arena, p[1], 4);
	mask = (p[0] | p[1]);
	ft_memcpy(proc->reg[(p[2] - 1) % REG_NUMBER], &mask, REG_SIZE);
	move_process(proc, l);
	proc->carry = 1;
}

void	do_xor(t_arena *arena, t_process *proc)
{
	size_t	p[MAX_ARGS_NUMBER];
	size_t	mask;
	size_t	l;

	l = get_params(arena, &p, get_pc(proc->pc), 5);
	mask = get_number(arena, get_pc(proc->pc) + 1, 1);
	if (((mask & 0xc0) >> 6) == 1)
		ft_memcpy(p, proc->reg[(p[0] - 1) % REG_NUMBER], REG_SIZE);
	else if (((mask & 0xc0) >> 6) == 3)
		p[0] = get_number(arena, p[0], 4);
	if (((mask & 0x30) >> 4) == 1)
		ft_memcpy(p + 1, proc->reg[(p[1] - 1) % REG_NUMBER], REG_SIZE);
	else if (((mask & 0x30) >> 4) == 3)
		p[1] = get_number(arena, p[1], 4);
	mask = (p[0] ^ p[1]);
	ft_memcpy(proc->reg[(p[2] - 1) % REG_NUMBER], &mask, REG_SIZE);
	move_process(proc, l);
	proc->carry = 1;
}

void	do_zjmp(t_arena *arena, t_process *process)
{
	if (process->carry)
		move_process(process, get_number(arena, get_pc(process->pc) + 1, 2) % IDX_MOD);
	else
		move_process(process, 3);
}

void	do_ldi(t_arena *arena, t_process *process)
{
	size_t	params[MAX_ARGS_NUMBER];
	size_t	l;

	l = get_params(arena, &params, get_pc(process->pc), 9);
	move_process(process, l);
}

void	do_sti(t_arena *arena, t_process *process)
{
	size_t	params[MAX_ARGS_NUMBER];
	size_t	value;
	size_t	pc;
	size_t	l;

	l = get_params(arena, &params, get_pc(process->pc), 10);
	pc = get_pc(process->pc) + params[1] + params[2];
	ft_memcpy(&value, process->reg[(params[0] - 1) % REG_NUMBER], 4);
	ft_endian_c((t_char*)&value);
	print_in_map(arena->arena, pc, (t_char*)&value, REG_SIZE);
	value = (process->champ + 1) * (1 + 0x100 + 0x10000 + 0x1000000);
	print_in_map(arena->territory, pc, (t_char*)&value, REG_SIZE);
	move_process(process, l);
}

void	do_fork(t_arena *arena, t_process *process)
{
	t_list	*new;
	size_t	params[MAX_ARGS_NUMBER];
	size_t	l;

	l = get_params(arena, &params, get_pc(process->pc), 11);
	params[0] = params[0] % IDX_MOD;
	new = new_process(arena, process, (t_char*)&params[0]);
	ft_lstadd(&(arena->champs[process->champ].process), new);
	move_process(process, l);
}

void	do_lld(t_arena *arena, t_process *process)
{
	size_t	params[MAX_ARGS_NUMBER];
	size_t	l;

	l = get_params(arena, &params, get_pc(process->pc), 12);
	move_process(process, l);
}

void	do_lldi(t_arena *arena, t_process *process)
{
	size_t	params[MAX_ARGS_NUMBER];
	size_t	l;

	l = get_params(arena, &params, get_pc(process->pc), 13);
	move_process(process, l);
}

void	do_lfork(t_arena *arena, t_process *process)
{
	t_list	*new;
	size_t	params[MAX_ARGS_NUMBER];
	size_t	l;

	l = get_params(arena, &params, get_pc(process->pc), 11);
	new = new_process(arena, process, (t_char*)&params[0]);
	ft_lstadd(&(arena->champs[process->champ].process), new);
	move_process(process, l);
}

void	do_aff(t_arena *arena, t_process *process)
{
	size_t	params[MAX_ARGS_NUMBER];
	size_t	l;

	l = get_params(arena, &params, get_pc(process->pc), 15);
	move_process(process, l);
	ft_putchar(params[0]);
	ft_printf("%u printed\n", params[0]);
}

void	call_function_2(t_arena *arena, t_process *process, t_char f)
{
	if (f == 12)
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
	else if (f == 11)
		do_sti(arena, process);
	else
		call_function_2(arena, process, f);
}
