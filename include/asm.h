/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 14:28:02 by pribault          #+#    #+#             */
/*   Updated: 2017/03/16 10:40:26 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include "ft_printf.h"

typedef struct	s_call
{
	int			pc;
	int			n;
	int			size;
	char		*label;
}				t_call;

typedef struct	s_label
{
	int			pc;
	char		*label;
}				t_label;

void	ft_error(int error, void *param);

#endif
