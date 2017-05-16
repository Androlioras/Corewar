/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 09:13:13 by pribault          #+#    #+#             */
/*   Updated: 2017/05/16 11:59:53 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

SDL_Color	g_colors[MAX_PLAYERS + 1][3] =
{
	{{32, 32, 32, 0}, {32, 32, 32, 0}, {32, 32, 32, 0}},
	{{0, 95, 1, 0}, {21, 210, 59, 0}, {0, 118, 0, 0}},
	{{2, 24, 109, 0}, {0, 130, 255, 0}, {0, 0, 185, 0}},
	{{95, 8, 0, 0}, {252, 42, 96, 0}, {150, 0, 0, 0}},
	{{115, 77, 3, 0}, {255, 255, 0, 0}, {255, 229, 0, 0}}
};

void	resize_window(t_win *win)
{
	win->w = (win->w > WIN_W_SIZE) ? WIN_W_SIZE : win->w;
	win->h = (win->h > WIN_H_SIZE) ? WIN_H_SIZE : win->h;
	SDL_SetWindowSize(win->win, win->w, win->h);
}

void	load_textures(t_win *win)
{
	SDL_Surface	*surface;
	char		s[3];
	t_uint		i;

	if (!(win->textures = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * 0x100 *
	(MAX_PLAYERS + 1) * 3)))
		return ;
	ft_printf("mem %u\n", 0x100 * (MAX_PLAYERS + 1) * 3);
	i = 0;
	s[2] = '\0';
	while (i < 0x100 * (MAX_PLAYERS + 1) * 3)
	{
		s[0] = HEXA[((i % 0x100) & 0xf0) >> 4];
		s[1] = HEXA[(i % 0x100) & 0xf];
		surface = TTF_RenderText_Solid(win->font, s,
		g_colors[(i / 0x100) % 5][(i / 0x100) / 5]);
		win->textures[i] = SDL_CreateTextureFromSurface(win->render, surface);
		SDL_FreeSurface(surface);
		i++;
	}
}

void	init_window(t_win *win)
{
	win->w = (win->w > WIN_W_SIZE) ? WIN_W_SIZE : win->w;
	win->h = (win->h > WIN_H_SIZE) ? WIN_H_SIZE : win->h;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		ft_error(8, (void*)SDL_GetError());
	if (TTF_Init() == -1)
		ft_error(666, NULL);
	if (!(win->win = SDL_CreateWindow(win->name, SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, win->w, win->h, SDL_WINDOW_SHOWN
	| SDL_WINDOW_RESIZABLE)))
		ft_error(8, (void*)SDL_GetError());
	if (!(win->render = SDL_CreateRenderer(win->win, -1,
	SDL_RENDERER_ACCELERATED)))
		ft_error(8, (void*)SDL_GetError());
	if (!(win->font = TTF_OpenFont("font.ttf", 64)))
		ft_error(9, NULL);
	load_textures(win);
}

void	quit_window(t_win *win)
{
	t_uint	i;

	i = 0;
	while (i < 0x100 * (MAX_PLAYERS + 1) * 3)
	{
		SDL_DestroyTexture(win->textures[i++]);
	}
	free(win->textures);
	SDL_DestroyRenderer(win->render);
	SDL_DestroyWindow(win->win);
	TTF_CloseFont(win->font);
	TTF_Quit();
	SDL_Quit();
}

void	draw_winner(t_arena *arena, t_win *win)
{
	ft_printf("cycle %u:\nle joueur %u(%s) a gagne\n",
	arena->cycle, arena->last + 1, arena->champs[arena->last].name);
	if (arena->flags.flags & 1)
	{
		while (!(win->stop & 2))
		{
			if (SDL_PollEvent(&(win->events)))
				ft_keys(arena, win);
			if ((arena->flags.flags & 3) && must_print())
				print_map(arena, win);
		}
	}
}
