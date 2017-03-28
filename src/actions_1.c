/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 13:12:44 by pribault          #+#    #+#             */
/*   Updated: 2017/03/28 20:00:52 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	do_live(t_arena *arena, t_process *process)
{
	t_uint	id;
	t_char	i;

	id = get_number(arena, get_pc(process->pc) + 1, 4);
	i = 0;
	while (i < arena->n)
	{
		if (arena->champs[i].id == id)
		{
			if (arena->flags.flags & 2)
				ft_printf("un processus dit que le joueur %d(%s) est en vie\n",
			i + 1, arena->champs[i].name);
			arena->lives++;
			arena->last = i;
		}
		i++;
	}
	process->living = 1;
	move_process(arena, process, 5);
}

void	do_ld(t_arena *arena, t_process *proc)
{
	t_uint	p[MAX_ARGS_NUMBER];
	t_uint	mask;
	t_uint	pc;
	t_uint	l;

	pc = get_pc(proc->pc);
	l = get_params(arena, &p, pc, 1);
	mask = get_number(arena, pc + 1, 1);
	if (((mask & 0xc0) >> 6) == 3)
	{
		idx(&pc, p[0]);
		p[0] = get_number(arena, pc, 4);
	}
	ft_memcpy(proc->reg[(p[1] - 1) % REG_NUMBER], p, REG_SIZE);
	proc->carry = (!p[0]) ? 1 : 0;
	move_process(arena, proc, l);
}

void	do_st(t_arena *arena, t_process *process)
{
	t_uint	p[MAX_ARGS_NUMBER];
	t_uint	value;
	t_uint	mask;
	t_uint	pc;
	t_uint	l;

	l = get_params(arena, &p, get_pc(process->pc), 2);
	mask = get_number(arena, get_pc(process->pc) + 1, 1);
	if (((mask & 0x30) >> 4) == 1)
		ft_memcpy(p + 1, process->reg[(p[1] - 1) % REG_NUMBER], REG_SIZE);
	pc = get_pc(process->pc);
	idx(&pc, p[1]);
	ft_memcpy(&value, process->reg[(p[0] - 1) % REG_NUMBER], 4);
	print_in_map(arena->arena, pc, (t_char*)&value, REG_SIZE);
	p[0] = (process->champ + 1) * (1 + 0x100 + 0x10000 + 0x1000000);
	print_in_map(arena->territory, pc, (t_char*)p, REG_SIZE);
	// process->carry = (!value) ? 1 : 0;
	move_process(arena, process, l);
}

void	do_add(t_arena *arena, t_process *process)
{
	t_uint	params[MAX_ARGS_NUMBER];
	t_uint	res;
	t_uint	l;

	l = get_params(arena, &params, get_pc(process->pc), 3);
	res = get_pc(process->reg[(params[0] - 1) % REG_NUMBER]);
	res += get_pc(process->reg[(params[1] - 1) % REG_NUMBER]);
	ft_endian_c((t_char*)&res);
	ft_memcpy(process->reg[(params[2] - 1) % REG_NUMBER], &res, REG_SIZE);
	process->carry = (!res) ? 1 : 0;
	move_process(arena, process, l);
}

void	do_sub(t_arena *arena, t_process *process)
{
	t_uint	params[MAX_ARGS_NUMBER];
	t_uint	res;
	t_uint	l;

	l = get_params(arena, &params, get_pc(process->pc), 4);
	res = get_pc(process->reg[(params[0] - 1) % REG_NUMBER]);
	res -= get_pc(process->reg[(params[1] - 1) % REG_NUMBER]);
	ft_endian_c((t_char*)&res);
	ft_memcpy(process->reg[(params[2] - 1) % REG_NUMBER], &res, REG_SIZE);
	process->carry = (!res) ? 1 : 0;
	move_process(arena, process, l);
}
