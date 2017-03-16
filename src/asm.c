/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 14:27:41 by pribault          #+#    #+#             */
/*   Updated: 2017/03/16 14:34:51 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	create_champ(int fd, char *name)
{
	char		tab[CHAMP_MAX_SIZE];
	size_t		len;
	t_header	header;

	len = 0;
	len++;
	name++;
	fd++;
	ft_bzero((void*)tab, CHAMP_MAX_SIZE);
	ft_bzero((void*)&header, sizeof(t_header));
}

int		main(int argc, char **argv)
{
	int		fd;

	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			ft_error(2, argv[1]);
		create_champ(fd, argv[1]);
		close(fd);
	}
	else
		ft_error(1, NULL);
	return (0);
}
