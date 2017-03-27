/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdouge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 03:32:38 by tdouge            #+#    #+#             */
/*   Updated: 2016/11/12 22:32:26 by tdouge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t result;

	result = (ft_strlen(dest) + ft_strlen(src));
	i = 0;
	j = 0;
	while (dest[i] && i < size)
		i++;
	if ((size - i) == 0)
		return (i + ft_strlen(src));
	while (src[j] && i != (size - 1))
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (result);
}
