/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdouge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 21:42:50 by tdouge            #+#    #+#             */
/*   Updated: 2016/11/12 22:24:13 by tdouge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim_split(char const *s, char c)
{
	char			*str;
	unsigned int	i;
	unsigned int	len;

	i = 0;
	if (!s || !c)
		return (NULL);
	len = ft_strlen(s);
	while (s[i] == c && s[i])
		i++;
	while ((len > i) && s[len - 1] == c && (len != 0))
		len--;
	if (i > len)
		return (NULL);
	str = ft_strsub(s, i, (len - i));
	return (str);
}
