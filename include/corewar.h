/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 14:28:06 by pribault          #+#    #+#             */
/*   Updated: 2017/03/26 13:05:59 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "ft_printf.h"
# include "op.h"
# include "SDL.h"
# include "SDL_TTF.h"
# include "OpenGL/gl3.h"
# include <sys/time.h>

# define ACTION_MAX_SIZE	8
# define WIN_W_SIZE			2560
# define WIN_H_SIZE			1440
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
	size_t			checks;
	size_t			speed;
}					t_arena;

typedef struct		s_win
{
	SDL_Window		*win;
	SDL_Renderer	*render;
	SDL_GLContext	context;
	SDL_Event		events;
	TTF_Font		*font;
	char			*name;
	int				w;
	int				h;
	t_char			stop;
	t_char			pause;
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

typedef struct		s_color
{
	t_char			r;
	t_char			g;
	t_char			b;
	t_char			a;
}					t_color;

void				ft_error(int error, void *param);

size_t				get_pc(t_char pc[REG_SIZE]);
size_t				get_number(t_arena *arena, size_t pc, t_char l);

void				move_process(t_arena *arena, t_process *process, size_t	n);

size_t				ft_endian(size_t n);
void				ft_endian_c(t_char *n);

void				virtual_machine(t_arena *arena, t_win *win);
void				print_map(t_arena *arena, t_win *win);

void				get_flags(t_arena *arena, int argc, char **argv);

void				create_champions(t_arena *arena, int n);

void				kill_champion(t_champ *champ);

void				creat_process(t_arena *arena, int n, int fd[MAX_PLAYERS]);
t_list				*new_process(t_arena *arena, t_process *father,
					t_char pc[4]);
void				free_process(t_arena *arena);

size_t				get_number(t_arena *arena, size_t pc, t_char l);
size_t				get_pc(t_char pc[REG_SIZE]);
void				print_in_map(t_char arena[MEM_SIZE], size_t pc, t_char *n,
					t_char l);
void				move_process(t_arena *arena, t_process *process, size_t n);

void				call_function(t_arena *arena, t_process *process, t_char f);

size_t				get_params(t_arena *ar, size_t (*p)[MAX_ARGS_NUMBER],
					size_t pc, t_char f);
t_char				verif_mask(size_t mask, t_char f);
void				idx(size_t *pc, size_t n);
void				print_in_map(t_char arena[MEM_SIZE], size_t pc, t_char *n,
					t_char l);

void				do_live(t_arena *arena, t_process *process);
void				do_ld(t_arena *arena, t_process *proc);
void				do_st(t_arena *arena, t_process *process);
void				do_add(t_arena *arena, t_process *process);
void				do_sub(t_arena *arena, t_process *process);
void				do_and(t_arena *arena, t_process *proc);
void				do_or(t_arena *arena, t_process *proc);
void				do_xor(t_arena *arena, t_process *proc);
void				do_zjmp(t_arena *arena, t_process *process);
void				do_ldi(t_arena *arena, t_process *proc);
void				do_sti(t_arena *arena, t_process *proc);
void				do_fork(t_arena *arena, t_process *process);
void				do_lld(t_arena *arena, t_process *proc);
void				do_lldi(t_arena *arena, t_process *process);
void				do_lfork(t_arena *arena, t_process *process);
void				do_aff(t_arena *arena, t_process *process);

void				init_window(t_win *win);
void				quit_window(t_win *win);

void				print_map(t_arena *arena, t_win *win);
void				print_text(t_win *win, char *text, SDL_Rect *rect,
					SDL_Color *color);

extern t_op		g_op[17];
extern t_color	g_colors[MAX_PLAYERS + 1][3];

#endif
