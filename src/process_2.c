/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 14:10:19 by pribault          #+#    #+#             */
/*   Updated: 2017/05/13 14:43:33 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_uint	process_number(t_arena *arena)
{
	t_list	*list;
	t_uint	n;

	list = arena->process;
	n = 0;
	while (list)
	{
		n++;
		list = list->next;
	}
	return (n);
}

void	kill_process(t_arena *arena, t_list **head, t_list *process)
{
	t_list	*list;
	t_uint	pc;

	list = *head;
	pc = get_pc(((t_process*)process->content)->pc) % MEM_SIZE;
	arena->territory[pc] = arena->territory[pc] % (MAX_PLAYERS + 1);
	arena->places[pc] += (arena->places[pc]) ? -1 : 0;
	free(process->content);
	if (*head != process)
	{
		while (list && list->next != process)
			list = list->next;
		list->next = process->next;
	}
	else
		*head = process->next;
	free(process);
}
