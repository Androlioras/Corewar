/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 14:28:06 by pribault          #+#    #+#             */
/*   Updated: 2017/03/21 14:10:55 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "ft_printf.h"
# include "op.h"
# include "SDL.h"
# include "OpenGL/gl3.h"
# include <sys/time.h>

# define ACTION_MAX_SIZE	8
# define WIN_W_SIZE			1920
# define WIN_H_SIZE			1080
# define MIN_FRAMERATE		60

typedef unsigned char	t_char;

typedef struct		s_flags
{
	size_t			flags;
}					t_flags;

typedef struct		s_process
{
	t_char			reg[REG_NUMBER][REG_SIZE];
	t_char			pc[REG_SIZE];
	char			waiting;
	char			carry;
	size_t			cycles;
	t_char			todo[ACTION_MAX_SIZE];
	size_t			champ;
}					t_process;

typedef struct		s_champ
{
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	size_t			len;
	size_t			live;
	size_t			id;
	t_list			*process;
}					t_champ;

typedef struct		s_arena
{
	t_flags			flags;
	t_char			arena[MEM_SIZE];
	t_char			territory[MEM_SIZE];
	t_champ			champs[MAX_PLAYERS];
	t_char			n;
	t_char			last;
	size_t			cycle;
	size_t			to_die;
	size_t			cycle_to_die;
}					t_arena;

typedef struct		s_win
{
	SDL_Window		*win;
	SDL_GLContext	context;
	SDL_Event		events;
	char			*name;
	int				w;
	int				h;
	t_char			stop;
}					t_win;

typedef struct		s_op
{
	char			*name;
	char			n_params;
	t_char			params[3];
	char			n;
	size_t			cycles;
	char			*comment;
	char			carry;
	char			modif;
}					t_op;

void				ft_error(int error, void *param);

size_t				get_pc(t_char pc[REG_SIZE]);
size_t				get_number(t_arena *arena, size_t pc, t_char l);

void				move_process(t_process *process, size_t	n);

size_t				ft_endian(size_t n);
void				ft_endian_c(t_char *n);

void				virtual_machine(t_arena *arena, t_win *win);
void				print_map(t_arena *arena, t_win *win);

void				get_flags(t_arena *arena, int argc, char **argv);

void				create_champions(t_arena *arena, int n);

void				kill_champion(t_champ *champ);

void				creat_process(t_arena *arena, int n, int fd[MAX_PLAYERS]);
t_list				*new_process(t_arena *arena, t_process *father, t_char pc[4]);
void				free_process(t_arena *arena);

void				call_function(t_arena *arena, t_process *process, t_char f);

void				init_window(t_win *win);
void				quit_window(t_win *win);

extern t_op	g_op[17];

#endif
