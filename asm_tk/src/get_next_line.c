/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdouge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 04:46:27 by tdouge            #+#    #+#             */
/*   Updated: 2017/02/03 20:41:23 by tdouge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/user.h"

int		ft_str_in_line(char *str, char **line)
{
	int		i;
	int		count;
	char	*tmp;

	i = 0;
	count = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
		count++;
	if (count > 0)
	{
		if (count > 0 && i == 0)
			return (1);
		tmp = (char *)malloc(sizeof(char) * (i) + 1);
		i = 0;
		count = 0;
		while (str[i] != '\n')
			tmp[i++] = str[count++];
		tmp[i] = '\0';
		*line = ft_strjoin_clean(*line, tmp);
		free(tmp);
		return (1);
	}
	return (0);
}

void	ft_del_buf(char **buf, char **line)
{
	int i;

	i = 0;
	while ((*buf)[i])
		i++;
	free(*line);
	(*line) = NULL;
	if (!(*line = (char *)malloc(sizeof(char) * (i) + 1)))
		return ((void)0);
	i = 0;
	while ((*buf)[i])
	{
		(*line)[i] = (*buf)[i];
		i++;
	}
	(*line)[i] = '\0';
	free(*buf);
	(*buf) = NULL;
}

int		ft_check(char **buf, char **line)
{
	int		i;
	int		count;
	char	*tmp;

	i = 0;
	count = 0;
	while ((*buf)[i] != '\n' && (*buf)[i])
		i++;
	if ((*buf)[i] == '\n')
		count++;
	if (count > 0)
	{
		*line = (char *)malloc(sizeof(char) * (i) + 1);
		i = 0;
		count = 0;
		while ((*buf)[i] != '\n' && (*buf)[i])
			(*line)[i++] = (*buf)[count++];
		(*line)[i] = '\0';
		tmp = *buf;
		*buf = ft_strdup(*buf + i + 1);
		free(tmp);
		return (1);
	}
	ft_del_buf(buf, line);
	return (0);
}

int		ft_return_buf(char *str, char **buf)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != '\n')
		i++;
	if (*buf != NULL)
		free(*buf);
	if (!(*buf = (char *)malloc(sizeof(char) * (BUFF_SIZE - i) + 1)))
		return (0);
	i++;
	while (str[i])
		(*buf)[j++] = str[i++];
	(*buf)[j] = '\0';
	free(str);
	return (1);
}

int		get_next_line(int const fd, char **line)
{
	int			ret;
	static char	*buf;
	char		*str;

	if (BUFF_SIZE < 0 || !line || fd < 0)
		return (-1);
	if (buf && buf[0] != '\0' && ft_check(&buf, line) == 1)
		return (1);
	if (*line == NULL)
		*line = ft_strnew(BUFF_SIZE);
	str = ft_strnew(BUFF_SIZE);
	while ((ret = read(fd, str, BUFF_SIZE)))
	{
		if (ret < 0)
			return (-1);
		if (ft_str_in_line(str, line) == 1 && ft_return_buf(str, &buf))
			return (1);
		*line = ft_strjoin_clean(*line, str);
		ft_bzero(((void *)str), BUFF_SIZE);
	}
	free(str);
	if (*line[0] == '\0')
		free(buf);
	return (*line[0] ? 1 : 0);
}
