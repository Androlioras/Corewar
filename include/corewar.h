/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 14:28:06 by pribault          #+#    #+#             */
/*   Updated: 2017/03/27 20:09:03 by pribault         ###   ########.fr       */
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
# define HEXA				"0123456789abcdef"

typedef unsigned char	t_char;
typedef unsigned int	t_uint;

typedef struct		s_flags
{
	t_uint			flags;
	t_uint			dump;
}					t_flags;

typedef struct		s_process
{
	t_char			reg[REG_NUMBER][REG_SIZE];
	t_char			pc[REG_SIZE];
	char			waiting;
	char			carry;
	t_uint			cycles;
	t_char			todo[ACTION_MAX_SIZE];
	t_uint			champ;
}					t_process;

typedef struct		s_champ
{
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	t_uint			len;
	t_uint			live;
	t_uint			id;
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
	t_uint			cycle;
	t_uint			to_die;
	t_uint			cycle_to_die;
	t_uint			checks;
	t_uint			speed;
}					t_arena;

typedef struct		s_win
{
	SDL_Window		*win;
	SDL_Renderer	*render;
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
	t_uint			cycles;
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

t_uint				get_pc(t_char pc[REG_SIZE]);
t_uint				get_number(t_arena *arena, t_uint pc, t_char l);

void				move_process(t_arena *arena, t_process *process, t_uint	n);

t_uint				ft_endian(t_uint n);
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

t_uint				get_number(t_arena *arena, t_uint pc, t_char l);
t_uint				get_pc(t_char pc[REG_SIZE]);
void				print_in_map(t_char arena[MEM_SIZE], t_uint pc, t_char *n,
					t_char l);
void				move_process(t_arena *arena, t_process *process, t_uint n);

void				call_function(t_arena *arena, t_process *process, t_char f);

t_uint				get_params(t_arena *ar, t_uint (*p)[MAX_ARGS_NUMBER],
					t_uint pc, t_char f);
t_char				verif_mask(t_uint mask, t_char f);
void				idx(t_uint *pc, t_uint n);
void				print_in_map(t_char arena[MEM_SIZE], t_uint pc, t_char *n,
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
void				draw_debug(t_arena *arena, t_win *win);
void				print_text(t_win *win, char *text, SDL_Rect *rect,
					SDL_Color *color);
void				print_and_exit(t_arena *arena, t_win *win);

extern t_op		g_op[17];
extern t_color	g_colors[MAX_PLAYERS + 1][3];

#endif
