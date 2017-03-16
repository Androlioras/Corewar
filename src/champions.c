/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 14:39:19 by pribault          #+#    #+#             */
/*   Updated: 2017/03/16 16:08:23 by pribault         ###   ########.fr       */
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

void	create_champions(t_arena *arena, int n)
{
	t_header	header;
	int			fd[n];
	int			i;

	i = 0;
	ft_bzero((void*)&header, sizeof(t_header));
	while (i < n)
	{
		if ((fd[i] = open(arena->champs[i].name, O_RDONLY)) == -1)
			ft_error(4, arena->champs[i].name);
		if (read(fd[i], (void*)&header, sizeof(t_header)) < (long)sizeof(t_header))
			ft_error(6, arena->champs[i].name);
		if (ft_endian(header.magic) != COREWAR_EXEC_MAGIC)
			ft_error(5, NULL);
		arena->champs[i].name = header.prog_name;
		arena->champs[i].comment = header.comment;
		arena->champs[i].len = header.prog_size;
		i++;
	}
	i = 0;
	while (i < n)
		close(fd[i++]);
}
