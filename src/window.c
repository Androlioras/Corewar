/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 09:13:13 by pribault          #+#    #+#             */
/*   Updated: 2017/03/20 12:39:21 by pribault         ###   ########.fr       */
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
	if (!(win->win = SDL_CreateWindow(win->name, SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, win->w, win->h, SDL_WINDOW_SHOWN |
	SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE)))
		ft_error(8, (void*)SDL_GetError());
	if (!(win->context = SDL_GL_CreateContext(win->win)))
		ft_error(8, (void*)SDL_GetError());
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
	SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
}

void	quit_window(t_win *win)
{
	SDL_DestroyWindow(win->win);
	SDL_GL_DeleteContext(win->context);
	SDL_Quit();
}
