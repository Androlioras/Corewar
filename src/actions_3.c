/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 13:22:56 by pribault          #+#    #+#             */
/*   Updated: 2017/05/15 11:37:08 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	do_sti(t_arena *arena, t_process *proc, t_uint p[MAX_ARGS_NUMBER])
{
	t_uint	value;
	t_uint	mask;
	t_uint	pc;

	mask = get_number(arena, get_pc(proc->pc) + 1, 1);
	if (((mask & 0x30) >> 4) == 1)
		p[1] = get_pc(proc->reg[(p[1] - 1) % REG_NUMBER]);
	else if (((mask & 0x30) >> 4) == 3)
		p[1] = get_number(arena, p[1], REG_SIZE);
	if (((mask & 0xc) >> 2) == 1)
		p[2] = get_pc(proc->reg[(p[2] - 1) % REG_NUMBER]);
	pc = get_pc(proc->pc) + p[1];
	idx(&pc, p[2]);
	ft_memcpy(&value, proc->reg[(p[0] - 1) % REG_NUMBER], REG_SIZE);
	print_in_map(arena->arena, pc, (t_char*)&value, REG_SIZE);
	value = (arena->territory[get_pc(proc->pc)] % 5 + 10) * 16843009;
	print_in_map(arena->territory, pc, (t_char*)&value, REG_SIZE);
}

void	do_fork(t_arena *arena, t_process *process, t_uint p[MAX_ARGS_NUMBER])
{
	t_list	*new;
	t_uint	param;
	t_uint	pc;

	p++;
	pc = get_pc(process->pc);
	param = get_number(arena, pc + 1, 2);
	idx(&pc, param);
	new = new_process(arena, process, (t_char*)&pc);
	if (new)
	{
		new->next = arena->process;
		arena->process = new;
		arena->territory[pc % MEM_SIZE] = process->champ + MAX_PLAYERS + 2;
		read_instruction(arena, (t_process*)new->content);
	}
}

void	do_lld(t_arena *arena, t_process *proc, t_uint p[MAX_ARGS_NUMBER])
{
	t_uint	mask;

	mask = get_number(arena, get_pc(proc->pc) + 1, 1);
	if (((mask & 0xc0) >> 6) == 3)
		p[0] = get_number(arena, p[0], REG_SIZE);
	ft_endian_c((t_char*)p);
	ft_memcpy(proc->reg[(p[1] - 1) % REG_NUMBER], p, REG_SIZE);
	proc->carry = (!p[0]) ? 1 : 0;
}

void	do_lldi(t_arena *arena, t_process *proc, t_uint p[MAX_ARGS_NUMBER])
{
	t_uint	mask;
	t_uint	v;

	mask = get_number(arena, get_pc(proc->pc) + 1, 1);
	if (((mask & 0xc0) >> 6) == 1)
		p[0] = get_pc(proc->reg[(p[0] - 1) % REG_NUMBER]);
	else if (((mask & 0xc0) >> 6) == 3)
		p[0] = get_number(arena, p[0], REG_SIZE);
	if (((mask & 0x30) >> 4) == 1)
		p[1] = get_pc(proc->reg[(p[1] - 1) % REG_NUMBER]);
	mask = get_pc(proc->pc) + p[0] + p[1];
	v = get_number(arena, mask, REG_SIZE);
	ft_endian_c((t_char*)&v);
	ft_memcpy(proc->reg[(p[2] - 1) % REG_NUMBER], &v, REG_SIZE);
	proc->carry = (!v) ? 1 : 0;
}

void	do_lfork(t_arena *arena, t_process *process, t_uint p[MAX_ARGS_NUMBER])
{
	t_list	*new;
	t_uint	param;
	t_uint	pc;

	p++;
	pc = get_pc(process->pc);
	param = pc + (get_number(arena, pc + 1, 2) % MEM_SIZE);
	new = new_process(arena, process, (t_char*)&pc);
	if (new)
	{
		new->next = arena->process;
		arena->process = new;
		arena->territory[pc % MEM_SIZE] = process->champ + MAX_PLAYERS + 2;
		read_instruction(arena, (t_process*)new->content);
	}
}
