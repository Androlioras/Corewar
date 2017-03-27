/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdouge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 18:17:16 by tdouge            #+#    #+#             */
/*   Updated: 2016/11/14 10:59:45 by tdouge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		value_max_neg_fd(int fd)
{
	ft_putchar_fd(('-'), fd);
	ft_putchar_fd(('2'), fd);
	ft_putchar_fd(('1'), fd);
	ft_putchar_fd(('4'), fd);
	ft_putchar_fd(('7'), fd);
	ft_putchar_fd(('4'), fd);
	ft_putchar_fd(('8'), fd);
	ft_putchar_fd(('3'), fd);
	ft_putchar_fd(('6'), fd);
	ft_putchar_fd(('4'), fd);
	ft_putchar_fd(('8'), fd);
}

void			ft_putnbr_fd(int nb, int fd)
{
	if (nb == -2147483648)
	{
		value_max_neg_fd(fd);
	}
	if (nb < 0 && nb != -2147483648)
	{
		ft_putchar_fd(('-'), fd);
		nb = -nb;
	}
	if (nb >= 10)
	{
		ft_putnbr_fd((nb / 10), fd);
		ft_putchar_fd((nb % 10 + '0'), fd);
	}
	else if (nb >= 0)
		ft_putchar_fd((nb + '0'), fd);
}
