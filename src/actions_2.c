/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 13:12:50 by pribault          #+#    #+#             */
/*   Updated: 2017/03/24 13:21:23 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	do_and(t_arena *arena, t_process *proc)
{
	size_t	p[MAX_ARGS_NUMBER];
	size_t	mask;
	size_t	l;

	l = get_params(arena, &p, get_pc(proc->pc), 5);
	mask = get_number(arena, get_pc(proc->pc) + 1, 1);
	proc->carry = 0;
	if (verif_mask(mask, 5))
	{
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
		proc->carry = 1;
	}
	move_process(arena, proc, l);
}

void	do_or(t_arena *arena, t_process *proc)
{
	size_t	p[MAX_ARGS_NUMBER];
	size_t	mask;
	size_t	l;

	l = get_params(arena, &p, get_pc(proc->pc), 6);
	mask = get_number(arena, get_pc(proc->pc) + 1, 1);
	proc->carry = 0;
	if (verif_mask(mask, 6))
	{
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
		proc->carry = 1;
	}
	move_process(arena, proc, l);
}

void	do_xor(t_arena *arena, t_process *proc)
{
	size_t	p[MAX_ARGS_NUMBER];
	size_t	mask;
	size_t	l;

	l = get_params(arena, &p, get_pc(proc->pc), 7);
	mask = get_number(arena, get_pc(proc->pc) + 1, 1);
	proc->carry = 0;
	if (verif_mask(mask, 7))
	{
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
		proc->carry = 1;
	}
	move_process(arena, proc, l);
}

void	do_zjmp(t_arena *arena, t_process *process)
{
	size_t	pc;
	size_t	n;

	pc = get_pc(process->pc);
	n = get_number(arena, pc + 1, 2);
	if (process->carry)
		move_process(arena, process, n);
	else
		move_process(arena, process, 3);
}

void	do_ldi(t_arena *arena, t_process *proc)
{
	size_t	p[MAX_ARGS_NUMBER];
	size_t	mask;
	size_t	v;
	size_t	l;

	l = get_params(arena, &p, get_pc(proc->pc), 9);
	mask = get_number(arena, get_pc(proc->pc) + 1, 1);
	if (verif_mask(mask, 9))
	{
		if (((mask & 0xc0) >> 6) == 1)
			ft_memcpy(p, proc->reg[(p[0] - 1) % REG_NUMBER], REG_SIZE);
		else if (((mask & 0xc0) >> 6) == 3)
			p[0] = get_number(arena, p[0], 4);
		if (((mask & 0x30) >> 4) == 1)
			ft_memcpy(p + 1, proc->reg[(p[1] - 1) % REG_NUMBER], REG_SIZE);
		else if (((mask & 0x30) >> 4) == 3)
			p[1] = get_number(arena, p[1], 4);
		v = get_number(arena, p[0] + p[1], REG_SIZE);
		ft_memcpy(proc->reg[(p[2] - 1) % REG_NUMBER], (t_char*)&v, REG_SIZE);
	}
	move_process(arena, proc, l);
}
