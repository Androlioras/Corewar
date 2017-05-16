/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   machine_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 13:34:08 by pribault          #+#    #+#             */
/*   Updated: 2017/05/13 10:16:46 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_uint	get_number(t_arena *arena, t_uint pc, t_char l)
{
	t_uint	n;
	t_uint	i;

	n = 0;
	i = 0;
	while (i < l)
	{
		n = n * 0x100 + arena->arena[(pc + i) % MEM_SIZE];
		i++;
	}
	return (n);
}

t_uint	get_npc(t_char *pc, t_uint size)
{
	t_uint	n;
	t_uint	i;

	n = 0;
	i = 0;
	while (i < size)
		n = n * 0x100 + pc[i++];
	return (n);
}

t_uint	get_pc(t_char pc[REG_SIZE])
{
	t_uint	n;
	t_uint	i;

	n = 0;
	i = 0;
	while (i < REG_SIZE)
		n = n * 0x100 + pc[i++];
	return (n);
}

void	print_in_map(t_char arena[MEM_SIZE], t_uint pc, t_char *n, t_char l)
{
	t_uint	i;

	i = 0;
	while (i < l)
	{
		arena[(pc + i) % MEM_SIZE] = n[i];
		i++;
	}
}

void	move_process(t_arena *arena, t_process *process, t_uint n)
{
	t_uint	pc;

	pc = get_pc(process->pc);
	arena->places[pc] += (arena->places[pc]) ? -1 : 0;
	if (!arena->places[pc])
		arena->territory[pc] = arena->territory[pc] % (MAX_PLAYERS + 1);
	pc = (pc + n) % MEM_SIZE;
	ft_memcpy(process->pc, &pc, REG_SIZE);
	arena->territory[pc] = arena->territory[pc] % (MAX_PLAYERS + 1) +
	(MAX_PLAYERS + 1);
	arena->places[pc]++;
	ft_endian_c(process->pc);
}
