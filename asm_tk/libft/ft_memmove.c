/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdouge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 22:15:43 by tdouge            #+#    #+#             */
/*   Updated: 2016/11/09 23:54:07 by tdouge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t i;

	i = 0;
	if (((char*)dest) > ((char*)src))
	{
		while (n != 0)
		{
			((char*)dest)[n - 1] = ((char*)src)[n - 1];
			n--;
		}
	}
	if (((char*)dest) < ((char*)src))
	{
		while (i < n)
		{
			((char*)dest)[i] = ((char*)src)[i];
			i++;
		}
	}
	return (dest);
}
