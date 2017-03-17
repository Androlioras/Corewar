/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 14:27:45 by pribault          #+#    #+#             */
/*   Updated: 2017/03/17 10:10:43 by pribault         ###   ########.fr       */
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
}

int		main(int argc, char **argv)
{
	t_arena	arena;

	arena.flags.flags = 0;
	ft_bzero(&arena.arena, MEM_SIZE);
	get_flags(&arena, argc, argv);
	print_map(&arena);
	return (0);
}
