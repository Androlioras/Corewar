/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 13:59:56 by pribault          #+#    #+#             */
/*   Updated: 2017/03/16 14:49:32 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	get_param(t_arena *arena, char *param)
{
	arena++;
	param++;
}

void	get_flags(t_arena *arena, int argc, char **argv)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		if (argv[i][0] == '-')
			get_param(arena, argv[i]);
		else if (j < MAX_PLAYERS)
			arena->champs[j++].name = argv[i];
		else
			ft_error(3, NULL);
		i++;
	}
	create_champions(arena, j);
}
