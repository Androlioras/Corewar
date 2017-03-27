/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdouge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 16:10:10 by tdouge            #+#    #+#             */
/*   Updated: 2016/12/05 05:41:02 by tdouge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*newstr;

	i = 0;
	if (!(newstr = (char *)malloc(sizeof(char) * size + 1)))
		return (0);
	while (i <= size)
	{
		newstr[i] = 0;
		i++;
	}
	return (newstr);
}
