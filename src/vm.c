/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 10:24:13 by pribault          #+#    #+#             */
/*   Updated: 2017/03/26 13:10:19 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	execute(t_arena *arena, t_process *process)
{
	process->waiting = 0;
	call_function(arena, process, process->todo[0]);
}

/*
**	remember that print_map must be remplaced in the future guys
*/

/*void	print_map(t_arena *arena, t_win *win)
{
	t_char	color[MAX_PLAYERS + 1];
	int		back;
	int		text;
	int		sqrt;
	int		tmp;
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
	ft_printf("cycle: %u\n", arena->cycle);
	while (i < sqrt)
	{
		j = 0;
		while (j < sqrt)
		{
			text = 255;
			back = color[arena->territory[i * sqrt + j] % (MAX_PLAYERS + 1)];
			if (arena->territory[i * sqrt + j] > MAX_PLAYERS + 1)
			{
				tmp = text;
				text = back;
				back = tmp;
			}
			printf("\033[48;5;%dm\033[38;5;%dm%.2hhx ", back, text, arena->arena[i * sqrt + j]);
			j++;
		}
		printf("\033[48;5;0m\n");
		i++;
	}
	ft_putchar('\n');
}*/

void	read_instruction(t_arena *arena, t_process *process)
{
	size_t	pc;
	size_t	i;

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

void	decrease(t_arena *arena, size_t lives)
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
		arena->champs[i++].live = 0;
	}
	decrease(arena, lives);
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
	if (!arena->to_die || arena->to_die > arena->cycle_to_die)
		verif_lives(arena, win);
	else
		arena->to_die--;
	while (i < arena->n)
	{
		list = arena->champs[i++].process;
		while (list)
		{
			process = (t_process*)list->content;
			if (process->waiting && process->cycles <= arena->cycle)
				execute(arena, process);
			if (!process->waiting)
				read_instruction(arena, process);
			list = list->next;
		}
	}
	arena->cycle++;
}
