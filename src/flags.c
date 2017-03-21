/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 13:59:56 by pribault          #+#    #+#             */
/*   Updated: 2017/03/21 15:19:10 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	get_param(t_arena *arena, char *param)
{
	if (!ft_strcmp(param, "-n") && !(arena->flags.flags & 1))
		arena->flags.flags += 1;
}

void	get_flags(t_arena *arena, int argc, char **argv)
{
	int		i;
	t_char	j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		if (argv[i][0] == '-')
			get_param(arena, argv[i]);
		else if (j < MAX_PLAYERS)
			ft_memcpy(arena->champs[j++].name, argv[i], ft_strlen(argv[i]) + 1);
		else
			ft_error(3, NULL);
		i++;
	}
	arena->n = j;
	ft_printf("name: %s\n", arena->champs[1].name);
	create_champions(arena, j);
}
