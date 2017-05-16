/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 14:06:03 by pribault          #+#    #+#             */
/*   Updated: 2017/05/12 17:51:21 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_JOINF_H
# define FT_JOINF_H

/*
**	includes
*/

# include "libft.h"
# include <stdarg.h>

/*
**	prototypes
*/

char	*ft_joinf(const char *format, ...);
int		ft_printj(const char *format, ...);

size_t	get_next_arg(va_list va, const char *format, size_t *i);
void	print_next_arg(va_list va, char *new, size_t *j, char c);
void	fill_string(va_list va, const char *format, char *new);

void	print_number(va_list va, char *new, size_t *j);
size_t	get_number_len(va_list va);

void	print_string(va_list va, char *new, size_t *j);
size_t	get_string_len(va_list va);

#endif
