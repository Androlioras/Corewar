/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 14:28:02 by pribault          #+#    #+#             */
/*   Updated: 2017/05/14 18:51:16 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include "ft_printf.h"

typedef unsigned char	t_char;
typedef unsigned int	t_uint;

typedef struct			s_op
{
	char				*name;
	char				n_params;
	t_char				params[3];
	char				n;
	t_uint				cycles;
	char				*comment;
	char				mask;
	char				modif;
}						t_op;

typedef struct			s_call
{
	int					pc;
	int					n;
	int					size;
	char				*label;
}						t_call;

typedef struct			s_label
{
	int					pc;
	char				*label;
}						t_label;

void					ft_error(int error, void *param);

extern t_op				g_op[17];

#endif
