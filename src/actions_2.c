/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 13:12:50 by pribault          #+#    #+#             */
/*   Updated: 2017/03/30 14:57:44 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	do_and(t_arena *arena, t_process *proc)
{
	t_uint	p[MAX_ARGS_NUMBER];
	t_uint	mask;
	t_uint	l;

	l = get_params(arena, &p, get_pc(proc->pc), 5);
	mask = get_number(arena, get_pc(proc->pc) + 1, 1);
	if (((mask & 0xc0) >> 6) == 1)
		p[0] = get_pc(proc->reg[(p[0] - 1) % REG_NUMBER]);
	else if (((mask & 0xc0) >> 6) == 3)
		p[0] = get_number(arena, p[0], 4);
	if (((mask & 0x30) >> 4) == 1)
		p[1] = get_pc(proc->reg[(p[1] - 1) % REG_NUMBER]);
	else if (((mask & 0x30) >> 4) == 3)
		p[1] = get_number(arena, p[1], 4);
	mask = (p[0] & p[1]);
	ft_endian_c((t_char*)&mask);
	ft_memcpy(proc->reg[(p[2] - 1) % REG_NUMBER], &mask, REG_SIZE);
	proc->carry = (!mask) ? 1 : 0;
	move_process(arena, proc, l);
}

void	do_or(t_arena *arena, t_process *proc)
{
	t_uint	p[MAX_ARGS_NUMBER];
	t_uint	mask;
	t_uint	l;

	l = get_params(arena, &p, get_pc(proc->pc), 6);
	mask = get_number(arena, get_pc(proc->pc) + 1, 1);
	if (((mask & 0xc0) >> 6) == 1)
		p[0] = get_pc(proc->reg[(p[0] - 1) % REG_NUMBER]);
	else if (((mask & 0xc0) >> 6) == 3)
		p[0] = get_number(arena, p[0], 4);
	if (((mask & 0x30) >> 4) == 1)
		p[1] = get_pc(proc->reg[(p[1] - 1) % REG_NUMBER]);
	else if (((mask & 0x30) >> 4) == 3)
		p[1] = get_number(arena, p[1], 4);
	mask = (p[0] | p[1]);
	ft_endian_c((t_char*)&mask);
	ft_memcpy(proc->reg[(p[2] - 1) % REG_NUMBER], &mask, REG_SIZE);
	proc->carry = (!mask) ? 1 : 0;
	move_process(arena, proc, l);
}

void	do_xor(t_arena *arena, t_process *proc)
{
	t_uint	p[MAX_ARGS_NUMBER];
	t_uint	mask;
	t_uint	l;

	l = get_params(arena, &p, get_pc(proc->pc), 7);
	mask = get_number(arena, get_pc(proc->pc) + 1, 1);
	if (((mask & 0xc0) >> 6) == 1)
		p[0] = get_pc(proc->reg[(p[0] - 1) % REG_NUMBER]);
	else if (((mask & 0xc0) >> 6) == 3)
		p[0] = get_number(arena, p[0], 4);
	if (((mask & 0x30) >> 4) == 1)
		p[1] = get_pc(proc->reg[(p[1] - 1) % REG_NUMBER]);
	else if (((mask & 0x30) >> 4) == 3)
		p[1] = get_number(arena, p[1], 4);
	mask = (p[0] ^ p[1]);
	ft_endian_c((t_char*)&mask);
	ft_memcpy(proc->reg[(p[2] - 1) % REG_NUMBER], &mask, REG_SIZE);
	proc->carry = (!mask) ? 1 : 0;
	move_process(arena, proc, l);
}

void	do_zjmp(t_arena *arena, t_process *process)
{
	t_uint	pc;
	t_uint	n;

	pc = get_pc(process->pc);
	n = get_number(arena, pc + 1, 2);
	if (process->carry)
		move_process(arena, process, n);
	else
		move_process(arena, process, 3);
}

void	do_ldi(t_arena *arena, t_process *proc)
{
	t_uint	p[MAX_ARGS_NUMBER];
	t_uint	mask;
	t_uint	v;
	t_uint	l;

	l = get_params(arena, &p, get_pc(proc->pc), 9);
	mask = get_number(arena, get_pc(proc->pc) + 1, 1);
	if (((mask & 0xc0) >> 6) == 1)
		p[0] = get_pc(proc->reg[(p[0] - 1) % REG_NUMBER]);
	else if (((mask & 0xc0) >> 6) == 3)
		p[0] = get_number(arena, p[0], 4);
	if (((mask & 0x30) >> 4) == 1)
		p[1] = get_pc(proc->reg[(p[1] - 1) % REG_NUMBER]);
	mask = get_pc(proc->pc);
	idx(&mask, p[0] + p[1]);
	v = get_number(arena, mask, REG_SIZE);
	ft_endian_c((t_char*)&v);
	ft_memcpy(proc->reg[(p[2] - 1) % REG_NUMBER], &v, REG_SIZE);
	// proc->carry = (!v) ? 1 : 0;
	move_process(arena, proc, l);
}
