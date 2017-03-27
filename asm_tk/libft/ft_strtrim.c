/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdouge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 03:06:08 by tdouge            #+#    #+#             */
/*   Updated: 2016/11/12 22:23:39 by tdouge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char			*str;
	unsigned int	i;
	unsigned int	len;

	i = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	while (ft_is_nul(s[i]) == 1 && s[i])
		i++;
	while ((len > i) && ft_is_nul(s[len - 1]) == 1 && (len != 0))
		len--;
	if (i > len)
		return (NULL);
	str = ft_strsub(s, i, (len - i));
	return (str);
}
