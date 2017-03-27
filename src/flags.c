/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 13:59:56 by pribault          #+#    #+#             */
/*   Updated: 2017/03/27 16:17:20 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	get_param(t_arena *arena, int argc, char **argv, int *i)
{
	if (!ft_strcmp(argv[*i], "-n") && !(arena->flags.flags & 1))
		arena->flags.flags += 1;
	else if (!ft_strcmp(argv[*i], "-debug") && !(arena->flags.flags & 2))
		arena->flags.flags += 2;
	else if (!ft_strcmp(argv[*i], "-dump") && !(arena->flags.flags & 4))
	{
		if ((*i) >= argc - 1)
			ft_error(11, NULL);
		arena->flags.flags += 4;
		(*i)++;
		arena->flags.dump = ft_atoi(argv[*i]);
	}
	else
		ft_error(10, argv[*i]);
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
			get_param(arena, argc, argv, &i);
		else if (j < MAX_PLAYERS)
			ft_memcpy(arena->champs[j++].name, argv[i], ft_strlen(argv[i]) + 1);
		else
			ft_error(3, NULL);
		i++;
	}
	arena->n = j;
	create_champions(arena, j);
}
