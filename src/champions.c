/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 14:39:19 by pribault          #+#    #+#             */
/*   Updated: 2017/03/21 14:12:05 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

size_t	ft_endian(size_t n)
{
	size_t	r;

	r = 0;
	r += ((n & 0xff000000) / 0x1000000);
	r += ((n & 0xff0000) / 0x100);
	r += ((n & 0xff00) * 0x100);
	r += ((n & 0xff) * 0x10000);
	return (r);
}

void	ft_endian_c(t_char *n)
{
	t_char	r[4];

	ft_memcpy(r, n, 4);
	n[0] = r[3];
	n[1] = r[2];
	n[2] = r[1];
	n[3] = r[0];
}

void	kill_champion(t_champ *champ)
{
	t_list	*list;
	t_list	*next;

	list = champ->process;
	while (list)
	{
		next = list->next;
		free(list->content);
		free(list);
		list = next;
	}
	champ->process = NULL;
	ft_printf("%s have been punched out by the virtual Foam bat\n", champ->name);
}

void	create_champions(t_arena *arena, int n)
{
	static t_header	header;
	int				fd[MAX_PLAYERS];
	int				i;

	i = 0;
	while (i < n)
	{
		if ((fd[i] = open(arena->champs[i].name, O_RDONLY)) == -1)
			ft_error(4, arena->champs[i].name);
		if (read(fd[i], &header, sizeof(t_header)) < (long)sizeof(t_header))
			ft_error(6, arena->champs[i].name);
		if (ft_endian(header.magic) != COREWAR_EXEC_MAGIC)
			ft_error(5, NULL);
		ft_memcpy(arena->champs[i].name, header.prog_name, PROG_NAME_LENGTH + 1);
		ft_memcpy(arena->champs[i].comment, header.comment, COMMENT_LENGTH + 1);
		arena->champs[i].len = header.prog_size;
		arena->champs[i].id = 0xffffffff - i;
		if (ft_endian(arena->champs[i].len) > CHAMP_MAX_SIZE)
			ft_error(7, arena->champs[i].name);
		i++;
	}
	i = 0;
	creat_process(arena, n, fd);
	while (i < n)
		close(fd[i++]);
}
