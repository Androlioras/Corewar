/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 13:12:44 by pribault          #+#    #+#             */
/*   Updated: 2017/03/24 13:13:41 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
	move_process(arena, process, 5);
}

void	do_ld(t_arena *arena, t_process *proc)
{
	size_t	p[MAX_ARGS_NUMBER];
	size_t	mask;
	size_t	l;

	l = get_params(arena, &p, get_pc(proc->pc), 1);
	mask = get_number(arena, get_pc(proc->pc) + 1, 1);
	proc->carry = 0;
	if (verif_mask(mask, 1))
	{
		if (((mask & 0xc0) >> 6) == 3)
			p[0] = get_number(arena, p[0], 4);
		ft_memcpy(proc->reg[(p[1] - 1) % REG_NUMBER], &p, REG_SIZE);
		proc->carry = 1;
	}
	move_process(arena, proc, l);
}

void	do_st(t_arena *arena, t_process *process)
{
	size_t	p[MAX_ARGS_NUMBER];
	size_t	value;
	size_t	mask;
	size_t	pc;
	size_t	l;

	l = get_params(arena, &p, get_pc(process->pc), 2);
	mask = get_number(arena, get_pc(process->pc) + 1, 1);
	process->carry = 0;
	if (verif_mask(mask, 2))
	{
		if (((mask & 0x30) >> 4) == 1)
			ft_memcpy(p + 1, process->reg[(p[1] - 1) % REG_NUMBER], REG_SIZE);
		pc = get_pc(process->pc);
		idx(&pc, p[1]);
		ft_memcpy(&value, process->reg[(p[0] - 1) % REG_NUMBER], REG_SIZE);
		ft_endian_c((t_char*)&value);
		print_in_map(arena->arena, pc, (t_char*)&value, REG_SIZE);
		p[0] = (process->champ + 1) * (1 + 0x100 + 0x10000 + 0x1000000);
		print_in_map(arena->territory, pc, (t_char*)p, REG_SIZE);
		process->carry = 1;
	}
	move_process(arena, process, l);
}

void	do_add(t_arena *arena, t_process *process)
{
	size_t	params[MAX_ARGS_NUMBER];
	size_t	res;
	size_t	l;

	l = get_params(arena, &params, get_pc(process->pc), 3);
	process->carry = 0;
	if (verif_mask(get_number(arena, get_pc(process->pc + 1) + 1, 1), 3))
	{
		res = ft_endian(get_pc(process->reg[(params[0] - 1) % REG_NUMBER]));
		res += ft_endian(get_pc(process->reg[(params[1] - 1) % REG_NUMBER]));
		ft_endian_c((t_char*)&res);
		ft_memcpy(process->reg[(params[2] - 1) % REG_NUMBER], &res, REG_SIZE);
		process->carry = 1;
	}
	move_process(arena, process, l);
}

void	do_sub(t_arena *arena, t_process *process)
{
	size_t	params[MAX_ARGS_NUMBER];
	size_t	res;
	size_t	l;

	l = get_params(arena, &params, get_pc(process->pc), 4);
	process->carry = 0;
	if (verif_mask(get_number(arena, get_pc(process->pc + 1) + 1, 1), 4))
	{
		res = ft_endian(get_pc(process->reg[(params[0] - 1) % REG_NUMBER]));
		res -= ft_endian(get_pc(process->reg[(params[1] - 1) % REG_NUMBER]));
		ft_endian_c((t_char*)&res);
		ft_memcpy(process->reg[(params[2] - 1) % REG_NUMBER], &res, REG_SIZE);
		process->carry = 1;
	}
	move_process(arena, process, l);
}
