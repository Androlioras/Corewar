/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 13:25:29 by pribault          #+#    #+#             */
/*   Updated: 2017/05/15 11:37:44 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	do_aff(t_arena *arena, t_process *process, t_uint p[MAX_ARGS_NUMBER])
{
	if (arena->flags.flags & 2)
		if (verif_mask(get_number(arena, get_pc(process->pc + 1) + 1, 1), 15))
			ft_putchar(p[0]);
}
