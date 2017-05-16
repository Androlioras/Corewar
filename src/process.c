/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 16:10:05 by pribault          #+#    #+#             */
/*   Updated: 2017/05/14 18:48:43 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_list	*new_process(t_arena *arena, t_process *father, t_char pc[4])
{
	t_list	*new;

	if (process_number(arena) >= 16384)
		return (NULL);
	if (!(new = ft_lstnew(father, sizeof(t_process))))
		return (NULL);
	ft_memcpy(((t_process*)(new->content))->pc, pc, REG_SIZE);
	ft_endian_c(((t_process*)(new->content))->pc);
	((t_process*)(new->content))->id = (arena->process) ?
	((t_process*)arena->process->content)->id + 1 : 1;
	return (new);
}

void	free_all_process(t_arena *arena)
{
	t_list	*list;
	t_list	*next;

	list = arena->process;
	while (list)
	{
		next = list->next;
		free(list->content);
		free(list);
		list = next;
	}
}

void	place_champion(t_arena *arena, int i, int fd, t_uint pc)
{
	char	code[CHAMP_MAX_SIZE];
	int		m;
	t_uint	j;

	m = ft_endian(arena->champs[i].len);
	if ((read(fd, code, m)) == -1)
		return ;
	ft_memcpy(arena->arena + pc, code, ft_endian(arena->champs[i].len));
	j = 0;
	while (j < ft_endian(arena->champs[i].len))
	{
		(arena->territory + pc)[j] = i + 1;
		j++;
	}
	(arena->territory + pc)[0] += MAX_PLAYERS + 1;
	arena->places[pc] += 1;
}

void	init_default(t_process *def)
{
	ft_bzero((void*)&(def->reg), sizeof(def->reg));
	ft_bzero((void*)&(def->pc), REG_SIZE);
	def->waiting = 0;
	def->living = 0;
	def->carry = 0;
	def->cycles = 0;
	def->champ = 0;
}

void	creat_process(t_arena *arena, int n, int fd[4])
{
	t_process	def;
	t_uint		pc;
	t_uint		id;
	int			i;

	i = 0;
	init_default(&def);
	while (i < n)
	{
		def.champ = (t_uint)i;
		id = get_pc((t_char*)&(arena->champs[i].id));
		ft_memcpy(def.reg[0], &id, REG_SIZE);
		pc = i * (MEM_SIZE / n);
		ft_printj("champion %s (%s) of %d bytes placed at %d\n",
		arena->champs[i].name, arena->champs[i].comment,
		ft_endian(arena->champs[i].len), pc);
		place_champion(arena, i, fd[i], pc);
		ft_lstadd(&arena->process, new_process(arena, &def, (t_char*)&pc));
		i++;
	}
}
