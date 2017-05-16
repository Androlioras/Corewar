/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 10:24:13 by pribault          #+#    #+#             */
/*   Updated: 2017/05/15 16:41:25 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	execute(t_arena *arena, t_process *process)
{
	t_uint	pc;

	pc = get_pc(process->pc);
	process->waiting = 0;
	if ((process->todo == 0 || process->todo > 16) && arena->arena[pc] > 0
	&& arena->arena[pc] < 17)
		read_instruction(arena, process);
	else
		call_function(arena, process, arena->arena[pc]);
}

void	read_instruction(t_arena *arena, t_process *process)
{
	t_uint	pc;

	pc = get_pc(process->pc) % MEM_SIZE;
	if (arena->arena[pc] < 1 || arena->arena[pc] > 16)
	{
		process->waiting = 1;
		process->cycles = arena->cycle + 1;
		process->todo = arena->arena[pc];
	}
	else
	{
		process->waiting = 1;
		process->cycles = arena->cycle +
		g_op[arena->arena[pc] - 1].cycles;
		process->todo = arena->arena[pc];
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
			kill_process(arena, &(arena->process), list);
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
	static char	n;
	t_list		*list;
	t_process	*process;

	n = (n == 10) ? 0 : n + 1;
	if (n == 10)
		clear_map(arena);
	if ((arena->flags.flags & 4) && arena->flags.dump <= arena->cycle)
		win->stop = 2;
	if (win->stop == 1)
		return ;
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
	if (!arena->to_die || arena->to_die > arena->cycle_to_die)
		verif_lives(arena, win);
	arena->to_die -= (arena->to_die) ? 1 : 0;
	arena->cycle += (!win->stop) ? 1 : 0;
}
