/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 10:24:13 by pribault          #+#    #+#             */
/*   Updated: 2017/03/17 13:45:48 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
			ft_printf("\033[48;5;%dm%.2hhx ", arena->arena[i * sqrt + j], arena->arena[i * sqrt + j]);
			j++;
		}
		ft_printf("\033[48;5;0m\n");
		i++;
	}
	ft_putchar('\n');
}

size_t	get_pc(t_char pc[4])
{
	size_t	n;

	n = 0;
	n += pc[0] * 0x1000000;
	n += pc[1] * 0x10000;
	n += pc[2] * 0x100;
	n += pc[3];
	return (n);
}

void	move_process(t_process *process, size_t	n)
{
	size_t	pc;

	pc = get_pc(process->pc);
	pc = (pc + n) % MEM_SIZE;
	ft_memcpy(process->pc, &pc, 4);
	ft_endian_c(process->pc);
}

void	read_instruction(t_arena *arena, t_process *process)
{
	size_t	pc;

	pc = get_pc(process->pc);
	if (arena->arena[pc] < 1 || arena->arena[pc] > 16)
		move_process(process, 1);
	arena++;
}

void	execute(t_arena *arena, t_process *process)
{
	arena++;
	process++;
}

void	virtual_machine(t_arena *arena)
{
	t_list		*list;
	t_process	*process;
	int			i;

	while (1)
	{
		getchar();
		i = 0;
		while (i < arena->n)
		{
			list = arena->champs[i++].process;
			while (list)
			{
				process = (t_process*)list->content;
				if (!process->waiting)
					read_instruction(arena, process);
				else if (process->cycles >= arena->cycle)
					execute(arena, process);
				list = list->next;
			}
		}
		print_map(arena);
		arena->cycle++;
	}
}
