/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 10:24:13 by pribault          #+#    #+#             */
/*   Updated: 2017/03/23 20:34:57 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

size_t	get_number(t_arena *arena, size_t pc, t_char l)
{
	size_t	n;
	size_t	i;

	n = 0;
	i = 0;
	while (i < l)
	{
		n = n * 0x100 + arena->arena[(pc + i) % MEM_SIZE];
		i++;
	}
	return (n);
}

size_t	get_pc(t_char pc[REG_SIZE])
{
	size_t	n;
	size_t	i;

	n = 0;
	i = 0;
	while (i < REG_SIZE)
		n = n * 0x100 + pc[i++];
	return (n);
}

void	move_process(t_process *process, size_t n)
{
	size_t	pc;

	pc = get_pc(process->pc);
	pc = (pc + n) % MEM_SIZE;
	ft_memcpy(process->pc, &pc, REG_SIZE);
	// ft_printf("process moved to: %u | n=%u\n", pc, n);
	ft_endian_c(process->pc);
}

void	execute(t_arena *arena, t_process *process)
{
	process->waiting = 0;
	call_function(arena, process, process->todo[0]);
}

void	print_map(t_arena *arena, t_win *win)
{
	t_char	color[MAX_PLAYERS + 1];
	int		sqrt;
	int		i;
	int		j;

	win++;
	sqrt = ft_sqrt(MEM_SIZE) + 1;
	i = 0;
	color[0] = 237;
	color[1] = 124;
	color[2] = 18;
	color[3] = 28;
	color[4] = 227;
	while (i < sqrt)
	{
		j = 0;
		while (j < sqrt)
		{
			printf("\033[48;5;%dm%.2hhx ", color[arena->territory[i * sqrt + j]], arena->arena[i * sqrt + j]);
			j++;
		}
		printf("\033[48;5;0m\n");
		i++;
	}
	ft_putchar('\n');
}

void	read_instruction(t_arena *arena, t_process *process)
{
	size_t	pc;
	size_t	i;

	pc = get_pc(process->pc);
	if (arena->arena[pc] < 1 || arena->arena[pc] > 16)
		move_process(process, 1);
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

void	verif_lives(t_arena *arena, t_win *win)
{
	size_t	lives;
	t_char	living;
	t_char	i;

	lives = 0;
	living = 0;
	i = 0;
	while (i < arena->n)
	{
		if (arena->champs[i].process)
			living++;
		lives += arena->champs[i].live;
		if (!arena->champs[i].live && arena->champs[i].process)
			kill_champion(&arena->champs[i]);
		else
			arena->last = i;
		arena->champs[i].live = 0;
		i++;
	}
	if (lives >= NBR_LIVE)
		arena->cycle_to_die -= CYCLE_DELTA;
	if (!living)
		win->stop = 1;
	arena->to_die = arena->cycle_to_die;
}

void	virtual_machine(t_arena *arena, t_win *win)
{
	t_list		*list;
	t_process	*process;
	t_char		i;

	i = 0;
	if (!arena->to_die)
		verif_lives(arena, win);
	else
		arena->to_die--;
	// printf("cycle:%lu | to die: %lu | cycle to die: %lu\n", arena->cycle, arena->to_die, arena->cycle_to_die);
	while (i < arena->n)
	{
		list = arena->champs[i++].process;
		while (list)
		{
			process = (t_process*)list->content;
			if (!process->waiting)
				read_instruction(arena, process);
			if (process->cycles <= arena->cycle)
				execute(arena, process);
			// if (process->waiting)
			// 	ft_printf("process is waiting for %s at %u\n", g_op[process->todo[0] - 1].name, get_pc(process->pc));
			// getchar();
			list = list->next;
		}
	}
	arena->cycle++;
}
