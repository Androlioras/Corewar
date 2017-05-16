/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 16:08:49 by pribault          #+#    #+#             */
/*   Updated: 2017/05/16 11:48:48 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_char	g_sh_c[MAX_PLAYERS + 1][3] =
{
	{242, 250, 246},
	{22, 47, 34},
	{18, 33, 20},
	{52, 197, 124},
	{94, 226, 214}
};

void	print_text(t_win *win, char *text, SDL_Rect *rect, SDL_Color *color)
{
	SDL_Texture	*texture;
	SDL_Surface	*surface;

	surface = TTF_RenderText_Solid(win->font, text, *color);
	texture = SDL_CreateTextureFromSurface(win->render, surface);
	SDL_FreeSurface(surface);
	SDL_RenderCopy(win->render, texture, NULL, rect);
	SDL_DestroyTexture(texture);
}

void	print_processes(t_arena *arena)
{
	t_list		*list;
	t_process	*process;
	int			i;

	list = arena->process;
	ft_printf("___ processes ___\n");
	while (list)
	{
		process = (t_process*)list->content;
		ft_printf("process %3u at %5u with carry %u\n", process->id,
		get_pc(process->pc), process->carry);
		if (arena->flags.flags & 2)
		{
			i = 0;
			while (i < REG_NUMBER)
			{
				ft_printf("	%-2u | %.2hhx %.2hhx %.2hhx %.2hhx\n", i + 1,
				process->reg[i][0], process->reg[i][1], process->reg[i][2],
				process->reg[i][3]);
				i++;
			}
		}
		list = list->next;
	}
	ft_printf("___ process number : %u___\n", process_number(arena));
}

void	print_p(t_char f, t_uint mask, t_uint p[MAX_ARGS_NUMBER])
{
	t_char	i;

	i = 0;
	while (i < g_op[f].n_params)
	{
		if ((mask & (192 >> 2 * i)) == (64 >> 2 * i))
			ft_printf("r%u", p[i]);
		else
			ft_printf("%d", (p[i] % MEM_SIZE > MEM_SIZE / 2) ?
			p[i] % MEM_SIZE - 4096 : p[i] % MEM_SIZE);
		i++;
		if (i != g_op[f].n_params)
			ft_putchar(',');
	}
}

void	draw_debug(t_arena *ar, t_win *win)
{
	int		sqrt;
	int		i;
	int		j;

	win++;
	sqrt = ft_sqrt(MEM_SIZE);
	i = 0;
	if (ar->flags.flags & 2)
		print_processes(ar);
	ft_printf("lives: %u\ncycle_to_die: %u\nto_die: %u\ndelta: %u\ncycle: %u\n",
	ar->lives, ar->cycle_to_die, ar->to_die, CYCLE_DELTA, ar->cycle);
	while (i < sqrt)
	{
		j = 0;
		while (j < sqrt)
		{
			ft_printf("\033[38;5;%hhum", g_sh_c[ar->territory[i * sqrt + j] %
			(MAX_PLAYERS + 1)][ar->territory[i * sqrt + j] /
			(MAX_PLAYERS + 1)]);
			ft_printf("%.2hhx\033[0m ", ar->arena[i * sqrt + j++]);
		}
		ft_printf("\n");
		i++;
	}
	ft_putchar('\n');
}

void	clear_map(t_arena *arena)
{
	t_char	value;
	int		sqrt;
	int		i;
	int		j;

	i = 0;
	sqrt = ft_sqrt(MEM_SIZE);
	while (i < sqrt)
	{
		j = 0;
		while (j < sqrt)
		{
			value = arena->territory[i * sqrt + j];
			if (value / (MAX_PLAYERS + 1) == 2)
				arena->territory[i * sqrt + j] = value % (MAX_PLAYERS + 1);
			j++;
		}
		i++;
	}
}
