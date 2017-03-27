/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdouge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 20:10:41 by tdouge            #+#    #+#             */
/*   Updated: 2016/11/14 23:11:15 by tdouge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t i;
	size_t j;
	size_t ind;

	i = 0;
	if (!*to_find)
		return ((char *)str);
	while (str[i] && len > 0)
	{
		j = 0;
		if (len < ft_strlen((char *)to_find))
			return (NULL);
		ind = i;
		while (str[ind] == to_find[j] && to_find[j] && str[ind])
		{
			ind++;
			j++;
		}
		if (to_find[j] == '\0')
			return ((char *)str + i);
		i++;
		len--;
	}
	return (NULL);
}
