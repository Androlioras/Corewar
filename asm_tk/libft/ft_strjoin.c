/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdouge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 16:08:10 by tdouge            #+#    #+#             */
/*   Updated: 2016/11/12 22:14:15 by tdouge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;

	i = 0;
	if (s1 && s2)
		i = ft_strlen(s1) + ft_strlen(s2);
	str = (char*)malloc(sizeof(*str) * (i + 1));
	if (!str)
		return (NULL);
	if (s1 && s2)
	{
		ft_strcpy(str, s1);
		ft_strcpy(str + ft_strlen(s1), s2);
	}
	return (str);
}
