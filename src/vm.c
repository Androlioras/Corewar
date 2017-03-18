/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ardanel <ardanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 10:24:13 by pribault          #+#    #+#             */
/*   Updated: 2017/03/18 22:04:51 by ardanel          ###   ########.fr       */
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

void	move_process(t_process *process, size_t	n)
{
	size_t	pc;

	pc = get_pc(process->pc);
	pc = (pc + n) % MEM_SIZE;
	ft_memcpy(process->pc, &pc, REG_SIZE);
	// ft_printf("pc moved to: %u | n=%u\n", pc, n);
	ft_endian_c(process->pc);
}

void	execute(t_arena *arena, t_process *process)
{
	call_function(arena, process, process->todo[0]);
	process->waiting = 0;
}

void	print_map(t_arena *arena)
{
	int		sqrt;
	int		i;
	int		j;

	sqrt = ft_sqrt(MEM_SIZE);
	i = 0;
	while (i <= sqrt)
	{
		j = 0;
		while (j <= sqrt)
		{
			printf("\033[48;5;%dm%.2hhx ", arena->arena[i * sqrt + j], arena->arena[i * sqrt + j]);
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
			process->todo[i] = arena->arena[pc + i];
			i++;
		}
		process->waiting = 1;
		process->cycles = arena->cycle + g_op[arena->arena[pc] - 1].cycles;
	}
}

void	virtual_machine(t_arena *arena)
{
	t_list		*list;
	t_process	*process;
	t_char		i;

	i = 0;
	ft_printf("cycle: %u\n", arena->cycle);
	while (i < arena->n)
	{
		list = arena->champs[i++].process;
		while (list)
		{
			process = (t_process*)list->content;
			// ft_printf("pc=%x\n", get_pc(process->pc));
			if (!process->waiting)
				read_instruction(arena, process);
			if (process->cycles <= arena->cycle)
				execute(arena, process);
			if (process->waiting)
				ft_printf("process is waiting for %s\n", g_op[process->todo[0] - 1].name);
			list = list->next;
		}
	}
	arena->cycle++;
}
