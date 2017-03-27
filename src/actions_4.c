/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 13:25:29 by pribault          #+#    #+#             */
/*   Updated: 2017/03/27 20:09:42 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	do_aff(t_arena *arena, t_process *process)
{
	t_uint	params[MAX_ARGS_NUMBER];
	t_uint	l;

	l = get_params(arena, &params, get_pc(process->pc), 15);
	if (verif_mask(get_number(arena, get_pc(process->pc + 1) + 1, 1), 15))
		ft_putchar(params[0]);
	move_process(arena, process, l);
}
