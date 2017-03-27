/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdouge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 04:01:28 by tdouge            #+#    #+#             */
/*   Updated: 2016/11/14 11:01:04 by tdouge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_nb_word(char const *s, char c)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c)
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static size_t	ft_nb_char(char const *s, int start, char c)
{
	int i;

	i = 0;
	while (s[start] != c && s[start])
	{
		i++;
		start++;
	}
	return (i);
}

char			**ft_strsplit(char const *s, char c)
{
	char	*sc;
	char	**str;
	int		nbword;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s || !c)
		return (NULL);
	sc = ft_strtrim_split(s, c);
	nbword = ft_nb_word(sc, c);
	if (!(str = (char **)malloc(sizeof(char *) * (nbword + 1))))
		return (NULL);
	while (nbword-- != 0)
	{
		str[j++] = ft_strsub(sc, i, ft_nb_char(sc, i, c));
		while (sc[i] != c && sc[i])
			i++;
		while (sc[i] == c && sc[i])
			i++;
	}
	str[j] = 0;
	free(sc);
	return (str);
}
