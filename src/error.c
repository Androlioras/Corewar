/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 09:38:53 by pribault          #+#    #+#             */
/*   Updated: 2017/03/16 09:55:24 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_error(int error, void *param)
{
	char	*s;

	if (error == 1)
		ft_putendl_fd("wrong number of arguments", 2);
	else if (error == 2)
	{
		s = ft_joinf("Can't read source file %s", (char*)param);
		ft_putendl_fd(s, 2);
		free(s);
	}
	if (error == 1 || error == 2)
		exit(1);
}
