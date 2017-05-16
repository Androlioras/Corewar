/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 09:38:53 by pribault          #+#    #+#             */
/*   Updated: 2017/05/15 16:58:11 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_error_3(int error, void *param)
{
	char	*s;

	if (error == 10)
	{
		s = ft_joinf("unknown argument: %s", (char*)param);
		ft_putendl_fd(s, 2);
		free(s);
	}
	else if (error == 11)
		ft_putendl_fd("-dump must be followed by an argument", 2);
	else if (error == 12)
		ft_putendl_fd("can't malloc textures", 2);
}

static void	ft_error_2(int error, void *param)
{
	char *s;

	if (error == 6)
	{
		s = ft_joinf("%s is too small to be a champion", (char*)param);
		ft_putendl_fd(s, 2);
		free(s);
	}
	else if (error == 7)
	{
		s = ft_joinf("%s is too faaaaaaaat", (char*)param);
		ft_putendl_fd(s, 2);
		free(s);
	}
	else if (error == 666)
		ft_putendl_fd("internal error. wtf ?!?", 2);
	else if (error == 8)
		ft_putendl_fd(param, 2);
	else if (error == 9)
		ft_putendl_fd("Can't open font", 2);
	else
		ft_error_3(error, param);
}

void		ft_error(int error, void *param)
{
	char	*s;

	if (error == 1)
		ft_putendl_fd("Wrong number of arguments", 2);
	else if (error == 2)
	{
		s = ft_joinf("Can't read source file %s", (char*)param);
		ft_putendl_fd(s, 2);
		free(s);
	}
	else if (error == 3)
		ft_putendl_fd("Too many champions", 2);
	else if (error == 4)
	{
		s = ft_joinf("Can't read champion file %s", (char*)param);
		ft_putendl_fd(s, 2);
		free(s);
	}
	else if (error == 5)
		ft_putendl_fd("Magiiiiiic :'(", 2);
	else
		ft_error_2(error, param);
	if ((error >= 1 && error <= 12) || error == 666)
		exit(1);
}
