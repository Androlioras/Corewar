/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 16:10:05 by pribault          #+#    #+#             */
/*   Updated: 2017/03/16 16:36:36 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

typedef struct	s_process
{
	char		reg[REG_NUMBER][REG_SIZE];
	char		pc[REG_SIZE];
	char		carry;
	size_t		cycles;
}				t_process;

t_list	*new_process(t_arena *arena, t_process *father)
{
	t_list	*new;
}

void	creat_process(t_arena *arena, int n)
{
	t_process	def;

	ft_bzero((void*)&(def.reg), REG_NUMBER * REG_SIZE);
	ft_bzero((void*)&(def.pc), REG_SIZE);
	def.carry = 0;
	def.cycles = 0;
	while (i < n)
	{
		if ((fd[i] = open(arena->champs[i].name, O_RDONLY)) == -1)
			ft_error(4, arena->champs[i].name);
	}
}