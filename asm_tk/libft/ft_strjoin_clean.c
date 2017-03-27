/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_clean.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdouge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 04:46:03 by tdouge            #+#    #+#             */
/*   Updated: 2016/12/14 04:46:09 by tdouge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_clean(char const *s1, char const *s2)
{
	char	*str;

	str = (char *)s1;
	s1 = ft_strjoin(s1, s2);
	free(str);
	return ((char *)s1);
}
