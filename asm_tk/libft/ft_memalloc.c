/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdouge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 15:43:13 by tdouge            #+#    #+#             */
/*   Updated: 2016/11/12 22:02:21 by tdouge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	int *tab;
	int i;

	i = 0;
	tab = (int*)malloc(sizeof(*tab) * (size));
	if (!tab)
		return (0);
	while (tab[i])
	{
		tab[i] = 0;
		i++;
	}
	return ((int*)tab);
}
