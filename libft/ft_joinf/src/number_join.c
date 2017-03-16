/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 14:06:03 by pribault          #+#    #+#             */
/*   Updated: 2017/03/15 14:57:16 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_joinf.h"
#include <stdio.h>

static size_t	numberlen(long long int nbr)
{
	size_t	len;

	len = 1;
	while (nbr / 10)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}

void			print_number(va_list va, char *new, size_t *j)
{
	long long int	nbr;
	long long int	save;

	nbr = va_arg(va, long long int);
	while (nbr)
	{
		save = nbr;
		while (nbr > 10)
			nbr /= 10;
		new[(*j)++] = '0' + nbr;
		while (nbr <= save / 10)
			nbr *= 10;
		nbr = save - nbr;
	}
}

size_t			get_number_len(va_list va)
{
	long long int	nbr;

	nbr = va_arg(va, long long int);
	return (numberlen(nbr));
}
