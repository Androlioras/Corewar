/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdouge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 05:01:18 by tdouge            #+#    #+#             */
/*   Updated: 2016/11/12 21:59:16 by tdouge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long int		ft_atoi(const char *str)
{
	long long int l;
	long long int neg;
	long long int nb;

	nb = 0;
	l = 0;
	neg = 0;
	while ((str[l] == ' ') || ((str[l] >= 9) && (str[l] <= 13)))
		l++;
	if (str[l] == '-')
		neg++;
	if (str[l] == '-' || str[l] == '+')
		l++;
	while ((str[l] >= '0') && (str[l] <= '9'))
	{
		nb = nb * 10;
		nb = nb + str[l] - 48;
		l++;
	}
	if (neg == 1)
		return (nb * -1);
	return (nb);
}
