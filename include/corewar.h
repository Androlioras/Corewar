/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 14:28:06 by pribault          #+#    #+#             */
/*   Updated: 2017/05/16 11:40:38 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

/*
**	includes
*/

# include "ft_printf.h"
# include "op.h"
# include "SDL.h"
# include "SDL_TTF.h"
# include "OpenGL/gl3.h"
# include <sys/time.h>

/*
**	defines
*/

# define ACTION_MAX_SIZE	8
# define WIN_W_SIZE			2560
# define WIN_H_SIZE			1440
# define MIN_FRAMERATE		60
# define HEXA				"0123456789abcdef"

/*
**	types
*/

typedef unsigned char	t_char;
typedef unsigned int	t_uint;

/*
**	strctures
*/

typedef struct		s_flags
{
	t_uint			flags;
	t_uint			dump;
}					t_flags;

typedef struct		s_process
{
	t_char			reg[REG_NUMBER][REG_SIZE];
	t_char			pc[REG_SIZE];
	t_char			todo;
	char			waiting;
	char			living;
	char			carry;
	t_uint			cycles;
	t_uint			champ;
	t_uint			id;
}					t_process;

typedef struct		s_champ
{
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	t_uint			len;
	t_uint			id;
}					t_champ;

typedef struct		s_arena
{
	t_flags			flags;
	t_char			arena[MEM_SIZE];
	t_char			territory[MEM_SIZE];
	t_char			places[MEM_SIZE];
	t_champ			champs[MAX_PLAYERS];
	t_list			*process;
	t_uint			lives;
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
	SDL_Texture		**textures;
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
	t_char			params[MAX_ARGS_NUMBER];
	char			n;
	t_uint			cycles;
	char			*comment;
	char			mask;
	char			modif;
}					t_op;

typedef struct		s_color
{
	t_char			r;
	t_char			g;
	t_char			b;
	t_char			a;
}					t_color;

/*
**	functions
*/

void				ft_error(int error, void *param);

t_uint				get_pc(t_char pc[REG_SIZE]);
t_uint				get_npc(t_char *pc, t_uint size);
t_uint				get_number(t_arena *arena, t_uint pc, t_char l);

void				move_process(t_arena *arena, t_process *process, t_uint	n);

t_uint				ft_endian(t_uint n);
void				ft_endian_c(t_char *n);

void				virtual_machine(t_arena *arena, t_win *win);
void				read_instruction(t_arena *arena, t_process *process);
void				execute(t_arena *arena, t_process *process);
void				print_map(t_arena *arena, t_win *win);

void				get_flags(t_arena *arena, int argc, char **argv);

void				create_champions(t_arena *arena, int n);

void				creat_process(t_arena *arena, int n, int fd[MAX_PLAYERS]);
t_list				*new_process(t_arena *arena, t_process *father,
					t_char pc[4]);
void				free_all_process(t_arena *arena);
void				kill_process(t_arena *arena, t_list **head, t_list *proc);
t_uint				process_number(t_arena *arena);

t_uint				get_number(t_arena *arena, t_uint pc, t_char l);
t_uint				get_pc(t_char pc[REG_SIZE]);
void				print_in_map(t_char arena[MEM_SIZE], t_uint pc, t_char *n,
					t_char l);
void				move_process(t_arena *arena, t_process *process, t_uint n);

void				call_function(t_arena *arena, t_process *process, t_char f);

t_char				verif_mask(t_char mask, t_char f);
void				idx(t_uint *pc, t_uint n);
void				print_in_map(t_char arena[MEM_SIZE], t_uint pc, t_char *n,
					t_char l);

void				do_live(t_arena *arena, t_process *process,
					t_uint p[MAX_ARGS_NUMBER]);
void				do_ld(t_arena *arena, t_process *proc,
					t_uint p[MAX_ARGS_NUMBER]);
void				do_st(t_arena *arena, t_process *process,
					t_uint p[MAX_ARGS_NUMBER]);
void				do_add(t_arena *arena, t_process *process,
					t_uint p[MAX_ARGS_NUMBER]);
void				do_sub(t_arena *arena, t_process *process,
					t_uint p[MAX_ARGS_NUMBER]);
void				do_and(t_arena *arena, t_process *proc,
					t_uint p[MAX_ARGS_NUMBER]);
void				do_or(t_arena *arena, t_process *proc,
					t_uint p[MAX_ARGS_NUMBER]);
void				do_xor(t_arena *arena, t_process *proc,
					t_uint p[MAX_ARGS_NUMBER]);
void				do_zjmp(t_arena *arena, t_process *process,
					t_uint p[MAX_ARGS_NUMBER]);
void				do_ldi(t_arena *arena, t_process *proc,
					t_uint p[MAX_ARGS_NUMBER]);
void				do_sti(t_arena *arena, t_process *proc,
					t_uint p[MAX_ARGS_NUMBER]);
void				do_fork(t_arena *arena, t_process *process,
					t_uint p[MAX_ARGS_NUMBER]);
void				do_lld(t_arena *arena, t_process *proc,
					t_uint p[MAX_ARGS_NUMBER]);
void				do_lldi(t_arena *arena, t_process *process,
					t_uint p[MAX_ARGS_NUMBER]);
void				do_lfork(t_arena *arena, t_process *process,
					t_uint p[MAX_ARGS_NUMBER]);
void				do_aff(t_arena *arena, t_process *process,
					t_uint p[MAX_ARGS_NUMBER]);

void				init_window(t_win *win);
void				quit_window(t_win *win);

void				ft_keys(t_arena *arena, t_win *win);
int					must_print(void);

void				print_p(t_char f, t_uint mask, t_uint p[MAX_ARGS_NUMBER]);
void				print_map(t_arena *arena, t_win *win);
void				clear_map(t_arena *arena);
void				draw_debug(t_arena *arena, t_win *win);
void				draw_winner(t_arena *arena, t_win *win);
void				print_text(t_win *win, char *text, SDL_Rect *rect,
					SDL_Color *color);
void				print_and_exit(t_arena *arena, t_win *win);

/*
**	extern variables
*/

extern t_op			g_op[17];
extern SDL_Color	g_colors[MAX_PLAYERS + 1][3];

#endif
