/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 13:12:44 by pribault          #+#    #+#             */
/*   Updated: 2017/05/15 11:39:33 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	do_live(t_arena *arena, t_process *process, t_uint p[MAX_ARGS_NUMBER])
{
	t_char	i;

	i = 0;
	while (i < arena->n)
	{
		if (arena->champs[i].id == p[0])
		{
			if (arena->flags.flags & 2)
			{
				ft_printj("\nun processus dit que le joueur %d", i + 1);
				ft_printj("(%s) est en vie\n\n", arena->champs[i].name);
			}
			arena->last = i;
		}
		i++;
	}
	arena->lives++;
	process->living = 1;
}

void	do_ld(t_arena *arena, t_process *proc, t_uint p[MAX_ARGS_NUMBER])
{
	t_uint	mask;
	t_uint	pc;

	pc = get_pc(proc->pc);
	mask = get_number(arena, pc + 1, 1);
	if (((mask & 0xc0) >> 6) == 3)
	{
		idx(&pc, p[0]);
		p[0] = get_number(arena, pc, REG_SIZE);
	}
	ft_endian_c((t_char*)p);
	ft_memcpy(proc->reg[(p[1] - 1) % REG_NUMBER], p, REG_SIZE);
	proc->carry = (!p[0]) ? 1 : 0;
}

void	do_st(t_arena *arena, t_process *process, t_uint p[MAX_ARGS_NUMBER])
{
	t_uint	value;
	t_uint	mask;
	t_uint	pc;

	pc = get_pc(process->pc);
	mask = get_number(arena, pc + 1, 1);
	if (((mask & 0x30) >> 4) == 1)
		p[1] = get_pc(process->reg[(p[1] - 1) % REG_NUMBER]);
	idx(&pc, p[1]);
	ft_memcpy(&value, process->reg[(p[0] - 1) % REG_NUMBER], REG_SIZE);
	print_in_map(arena->arena, pc, (t_char*)&value, REG_SIZE);
	p[0] = (arena->territory[get_pc(process->pc)] % 5 + 10) * 16843009;
	print_in_map(arena->territory, pc, (t_char*)p, REG_SIZE);
}

void	do_add(t_arena *arena, t_process *process, t_uint p[MAX_ARGS_NUMBER])
{
	t_uint	res;

	arena++;
	res = get_pc(process->reg[(p[0] - 1) % REG_NUMBER]);
	res += get_pc(process->reg[(p[1] - 1) % REG_NUMBER]);
	ft_endian_c((t_char*)&res);
	ft_memcpy(process->reg[(p[2] - 1) % REG_NUMBER], &res, REG_SIZE);
	process->carry = (!res) ? 1 : 0;
}

void	do_sub(t_arena *arena, t_process *process, t_uint p[MAX_ARGS_NUMBER])
{
	t_uint	res;

	arena++;
	res = get_pc(process->reg[(p[0] - 1) % REG_NUMBER]);
	res -= get_pc(process->reg[(p[1] - 1) % REG_NUMBER]);
	ft_endian_c((t_char*)&res);
	ft_memcpy(process->reg[(p[2] - 1) % REG_NUMBER], &res, REG_SIZE);
	process->carry = (!res) ? 1 : 0;
}
