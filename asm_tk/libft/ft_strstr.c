/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdouge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 18:03:55 by tdouge            #+#    #+#             */
/*   Updated: 2016/11/12 22:22:21 by tdouge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *meule, char *aigu)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (aigu[i] == '\0')
		return (&meule[i]);
	while (meule[i])
	{
		if (aigu[j] == meule[i])
			j++;
		else
		{
			i = i - j;
			j = 0;
		}
		i++;
		if (aigu[j] == '\0')
		{
			i = i - j;
			return (&meule[i]);
		}
	}
	return (0);
}
