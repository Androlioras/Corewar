/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 14:10:19 by pribault          #+#    #+#             */
/*   Updated: 2017/03/28 15:55:00 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	kill_process(t_list **head, t_list *process)
{
	t_list	*list;

	list = *head;
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
