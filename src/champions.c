/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 14:39:19 by pribault          #+#    #+#             */
/*   Updated: 2017/05/15 10:48:57 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_uint	ft_endian(t_uint n)
{
	t_uint	r;

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

void	create_champions(t_arena *ar, int n)
{
	static t_header	header;
	int				fd[MAX_PLAYERS];
	int				i;

	i = 0;
	while (i < n)
	{
		if ((fd[i] = open(ar->champs[i].name, O_RDONLY)) == -1)
			ft_error(4, ar->champs[i].name);
		if (read(fd[i], &header, sizeof(t_header)) < (long)sizeof(t_header))
			ft_error(6, ar->champs[i].name);
		if (ft_endian(header.magic) != COREWAR_EXEC_MAGIC)
			ft_error(5, NULL);
		ft_memcpy(ar->champs[i].name, header.prog_name, PROG_NAME_LENGTH + 1);
		ft_memcpy(ar->champs[i].comment, header.comment, COMMENT_LENGTH + 1);
		ar->champs[i].len = header.prog_size;
		ar->champs[i].id = 0xffffffff - i;
		ar->last = i;
		if (ft_endian(ar->champs[i++].len) > CHAMP_MAX_SIZE)
			ft_error(7, ar->champs[i - 1].name);
	}
	i = 0;
	creat_process(ar, n, fd);
	while (i < n)
		close(fd[i++]);
}
