/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 10:24:13 by pribault          #+#    #+#             */
/*   Updated: 2017/03/17 12:06:26 by pribault         ###   ########.fr       */
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

void	virtual_machine(t_arena *arena)
{
	while (1)
	{
		getchar();
		print_map(arena);
		arena->cycle++;
	}
}
