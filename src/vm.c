/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 10:24:13 by pribault          #+#    #+#             */
/*   Updated: 2017/03/28 15:57:39 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	execute(t_arena *arena, t_process *process)
{
	process->waiting = 0;
	call_function(arena, process, process->todo[0]);
}

void	read_instruction(t_arena *arena, t_process *process)
{
	t_uint	pc;
	t_uint	i;

	pc = get_pc(process->pc);
	if (arena->arena[pc] < 1 || arena->arena[pc] > 16)
		move_process(arena, process, 1);
	else
	{
		i = 0;
		while (i < ACTION_MAX_SIZE)
		{
			process->todo[i] = arena->arena[(pc + i) % MEM_SIZE];
			i++;
		}
		process->waiting = 1;
		process->cycles = arena->cycle + g_op[arena->arena[pc] - 1].cycles;
	}
}

void	decrease(t_arena *arena, t_uint lives)
{
	arena->checks += (lives < NBR_LIVE) ? 1 : 0;
	if (arena->checks >= MAX_CHECKS || lives >= NBR_LIVE)
	{
		if (arena->cycle_to_die > CYCLE_DELTA)
			arena->cycle_to_die -= CYCLE_DELTA;
		else
			arena->cycle_to_die -= arena->cycle_to_die;
		arena->checks = 0;
	}
}

void	verif_lives(t_arena *arena, t_win *win)
{
	t_process	*process;
	t_list		*list;

	list = arena->process;
	while (list)
	{
		process = (t_process*)list->content;
		if (!process->living)
			kill_process(&(arena->process), list);
		else
			process->living = 0;
		list = list->next;
	}
	decrease(arena, arena->lives);
	if (!arena->lives)
		win->stop = 1;
	arena->lives = 0;
	arena->to_die = arena->cycle_to_die;
}

void	virtual_machine(t_arena *arena, t_win *win)
{
	t_list		*list;
	t_process	*process;

	if ((arena->flags.flags & 4) && arena->flags.dump <= arena->cycle)
		win->stop = 1;
	if (!arena->to_die || arena->to_die > arena->cycle_to_die)
		verif_lives(arena, win);
	else
		arena->to_die--;
	list = arena->process;
	while (list)
	{
		process = (t_process*)list->content;
		if (process->waiting && process->cycles <= arena->cycle)
			execute(arena, process);
		if (!process->waiting)
			read_instruction(arena, process);
		list = list->next;
	}
	arena->cycle++;
}
