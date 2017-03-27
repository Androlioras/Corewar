/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdouge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 15:38:38 by tdouge            #+#    #+#             */
/*   Updated: 2016/11/12 22:22:47 by tdouge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		j;
	char		*str;

	if (!s)
		return (NULL);
	if (((size_t)start + (size_t)len) > ft_strlen((char*)s))
		return (0);
	i = start;
	j = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (len == 0)
	{
		str[j] = '\0';
		return (str);
	}
	while ((s[i] != '\0') && (i < (start + len)))
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}
