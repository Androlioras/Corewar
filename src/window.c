/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 09:13:13 by pribault          #+#    #+#             */
/*   Updated: 2017/03/27 20:12:36 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	resize_window(t_win *win)
{
	win->w = (win->w > WIN_W_SIZE) ? WIN_W_SIZE : win->w;
	win->h = (win->h > WIN_H_SIZE) ? WIN_H_SIZE : win->h;
	SDL_SetWindowSize(win->win, win->w, win->h);
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
}

void	quit_window(t_win *win)
{
	SDL_DestroyRenderer(win->render);
	SDL_DestroyWindow(win->win);
	TTF_CloseFont(win->font);
	TTF_Quit();
	SDL_Quit();
}
