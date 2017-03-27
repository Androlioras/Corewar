/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdouge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 02:52:03 by tdouge            #+#    #+#             */
/*   Updated: 2016/11/14 10:53:24 by tdouge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_nb_malloc(int n)
{
	int count;
	int tmp;

	tmp = n;
	count = 0;
	while (tmp > 0)
	{
		tmp = tmp / 10;
		count++;
	}
	return (count);
}

static char		*ft_neg_itoa(int n)
{
	char	*str;
	int		tmp;
	int		count;

	tmp = n * -1;
	count = 1;
	while (tmp > 0)
	{
		tmp = tmp / 10;
		count++;
	}
	tmp = n * -1;
	if (!(str = (char *)malloc(sizeof(*str) * (count) + 1)))
		return (NULL);
	str[count] = '\0';
	while (tmp > 0)
	{
		str[--count] = (tmp % 10) + '0';
		tmp = tmp / 10;
	}
	str[0] = '-';
	return (str);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		tmp;
	int		count;

	tmp = n;
	count = ft_nb_malloc(n);
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		return (ft_neg_itoa(n));
	if (!(str = (char *)malloc(sizeof(*str) * (count) + 1)))
		return (NULL);
	str[count] = '\0';
	while (tmp > 0)
	{
		str[--count] = (tmp % 10) + '0';
		tmp = tmp / 10;
	}
	return (str);
}
