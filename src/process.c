/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 16:10:05 by pribault          #+#    #+#             */
/*   Updated: 2017/03/17 12:10:50 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_list	*new_process(t_arena *arena, t_process *father, char pc[4])
{
	t_list	*new;

	if (!(new = ft_lstnew(father, sizeof(t_process))))
		return (NULL);
	ft_memcpy(((t_process*)(new->content))->pc, pc, 4);
	ft_endian_c(((t_process*)(new->content))->pc);
	ft_lstadd(&(arena->active), new);
	ft_printf("new process at: %u\n", ft_endian(*(size_t*)(((t_process*)(new->content))->pc)));
	return (new);
}

void	place_champion(t_arena *arena, int i, int fd, size_t pc)
{
	char	code[CHAMP_MAX_SIZE];
	int		m;
	int		j;

	m = ft_endian(arena->champs[i].len);
	if ((read(fd, code, m)) == -1)
		return ;
	j = 0;
	while (j < m)
	{
		arena->arena[pc + j] = code[j];
		j++;
	}
	// ft_memcpy(arena->arena + pc, code, ft_endian(arena->champs[i].len));
}

void	creat_process(t_arena *arena, int n, int fd[4])
{
	t_process	def;
	size_t		pc;
	int			l;
	int			i;
	int			e;

	ft_bzero((void*)&(def.reg), REG_NUMBER * REG_SIZE);
	ft_bzero((void*)&(def.pc), REG_SIZE);
	def.waiting = 0;
	def.carry = 0;
	def.cycles = 0;
	i = 0;
	l = 0;
	while (i < n)
		l += ft_endian(arena->champs[i++].len);
	i = 0;
	e = (MEM_SIZE - l) / n;
	while (i < n)
	{
		ft_printf("%d\n", ft_endian(arena->champs[i].len));
		pc = (i == 0) ? 0 : pc + ft_endian(arena->champs[i - 1].len) + e;
		place_champion(arena, i, fd[i], pc);
		arena->champs[i].process = new_process(arena, &def, (char*)&pc);
		i++;
	}
}
