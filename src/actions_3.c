/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 13:22:56 by pribault          #+#    #+#             */
/*   Updated: 2017/03/24 13:23:26 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	do_sti(t_arena *arena, t_process *proc)
{
	size_t	p[MAX_ARGS_NUMBER];
	size_t	value;
	size_t	mask;
	size_t	pc;
	size_t	l;

	l = get_params(arena, &p, get_pc(proc->pc), 10);
	mask = get_number(arena, get_pc(proc->pc) + 1, 1);
	if (verif_mask(mask, 10))
	{
		if (((mask & 0x30) >> 4) == 1)
			ft_memcpy(p + 1, proc->reg[(p[1] - 1) % REG_NUMBER], REG_SIZE);
		else if (((mask & 0x30) >> 4) == 3)
			p[1] = get_number(arena, p[1], 4);
		if (((mask & 0xc) >> 2) == 1)
			ft_memcpy(p + 2, proc->reg[(p[2] - 1) % REG_NUMBER], REG_SIZE);
		pc = get_pc(proc->pc) + p[1] + p[2];
		ft_memcpy(&value, proc->reg[(p[0] - 1) % REG_NUMBER], 4);
		ft_endian_c((t_char*)&value);
		print_in_map(arena->arena, pc, (t_char*)&value, REG_SIZE);
		value = (proc->champ + 1) * (1 + 0x100 + 0x10000 + 0x1000000);
		print_in_map(arena->territory, pc, (t_char*)&value, REG_SIZE);
	}
	move_process(arena, proc, l);
}

void	do_fork(t_arena *arena, t_process *process)
{
	t_list	*new;
	size_t	param;
	size_t	pc;

	pc = get_pc(process->pc);
	param = get_number(arena, pc + 1, 2) % MEM_SIZE;
	idx(&pc, param);
	new = arena->champs[process->champ].process;
	while (new->next)
		new = new->next;
	new->next = new_process(arena, process, (t_char*)&pc);
	move_process(arena, process, 3);
}

void	do_lld(t_arena *arena, t_process *proc)
{
	size_t	p[MAX_ARGS_NUMBER];
	size_t	mask;
	size_t	l;

	l = get_params(arena, &p, get_pc(proc->pc), 12);
	mask = get_number(arena, get_pc(proc->pc) + 1, 1);
	proc->carry = 0;
	if (verif_mask(mask, 12))
	{
		if (((mask & 0xc0) >> 6) == 3)
			p[0] = get_number(arena, p[0], 4);
		ft_memcpy(proc->reg[(p[1] - 1) % REG_NUMBER], &p, REG_SIZE);
		proc->carry = 1;
	}
	move_process(arena, proc, l);
}

void	do_lldi(t_arena *arena, t_process *process)
{
	size_t	params[MAX_ARGS_NUMBER];
	size_t	l;

	l = get_params(arena, &params, get_pc(process->pc), 13);
	move_process(arena, process, l);
}

void	do_lfork(t_arena *arena, t_process *process)
{
	t_list	*new;
	size_t	param;
	size_t	pc;

	pc = get_pc(process->pc);
	param = pc + (get_number(arena, pc + 1, 2) % MEM_SIZE);
	new = arena->champs[process->champ].process;
	while (new->next)
		new = new->next;
	new->next = new_process(arena, process, (t_char*)&pc);
	move_process(arena, process, 3);
}
