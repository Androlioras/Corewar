/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 14:27:45 by pribault          #+#    #+#             */
/*   Updated: 2017/05/16 11:58:39 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_keys(t_arena *arena, t_win *win)
{
	if (win->events.type == SDL_WINDOWEVENT)
	{
		if (win->events.window.event == SDL_WINDOWEVENT_CLOSE)
			win->stop += (!(win->stop & 2)) ? 2 : 0;
		else if (win->events.window.event == SDL_WINDOWEVENT_RESIZED)
			SDL_GetWindowSize(win->win, &(win->w), &(win->h));
	}
	else if (win->events.type == SDL_KEYDOWN)
	{
		if (win->events.key.keysym.sym == SDLK_SPACE)
		{
			if (!win->events.key.repeat && win->events.key.type == SDL_KEYDOWN)
				win->pause = (win->pause) ? 0 : 1;
		}
		else if (win->events.key.keysym.sym == SDLK_ESCAPE)
			win->stop += (!(win->stop & 2)) ? 2 : 0;
		else if (win->events.key.keysym.sym == SDLK_RIGHT)
			arena->speed += 10;
		else if (win->events.key.keysym.sym == SDLK_LEFT && arena->speed >= 10)
			arena->speed -= 10;
		else if (win->events.key.keysym.sym == SDLK_d)
			draw_debug(arena, win);
	}
}

int		must_print(void)
{
	static struct timeval	prev;
	static struct timeval	t;

	gettimeofday(&t, NULL);
	if (t.tv_sec - prev.tv_sec >= (double)1 / MIN_FRAMERATE)
	{
		prev = t;
		return (1);
	}
	else if (t.tv_usec - prev.tv_usec >= (double)1000000 / MIN_FRAMERATE)
	{
		prev = t;
		return (1);
	}
	return (0);
}

int		must_run(t_arena *arena)
{
	static struct timeval	prev;
	static struct timeval	t;

	gettimeofday(&t, NULL);
	if (t.tv_sec - prev.tv_sec >= (double)1 / arena->speed)
	{
		prev = t;
		return (1);
	}
	else if (t.tv_usec - prev.tv_usec >= (double)1000000 / arena->speed)
	{
		prev = t;
		return (1);
	}
	return (0);
}

void	ft_init(t_arena *arena, t_win *win)
{
	arena->flags.flags = 0;
	arena->flags.dump = 0;
	arena->cycle = 0;
	arena->cycle_to_die = CYCLE_TO_DIE;
	arena->to_die = CYCLE_TO_DIE;
	arena->speed = 10;
	arena->last = MAX_PLAYERS;
	arena->lives = 0;
	arena->checks = 0;
	arena->process = NULL;
	ft_bzero(&arena->arena, MEM_SIZE);
	ft_bzero(&arena->territory, MEM_SIZE);
	ft_bzero(&arena->places, MEM_SIZE);
	win->name = "Corewar";
	win->w = 1000;
	win->h = 562;
	win->stop = 0;
	win->pause = 1;
}

int		main(int argc, char **argv)
{
	t_win	win;
	t_arena	arena;

	ft_init(&arena, &win);
	get_flags(&arena, argc, argv);
	if (arena.flags.flags & 1)
		init_window(&win);
	while (!win.stop)
	{
		if (SDL_PollEvent(&(win.events)))
			ft_keys(&arena, &win);
		if (!(arena.flags.flags & 1) || (!win.pause && must_run(&arena)))
			virtual_machine(&arena, &win);
		if ((arena.flags.flags & 3) && must_print())
			print_map(&arena, &win);
	}
	if (arena.flags.flags & 4)
		draw_debug(&arena, &win);
	if ((win.stop & 1) && arena.last < MAX_PLAYERS)
		draw_winner(&arena, &win);
	free_all_process(&arena);
	if (arena.flags.flags & 1)
		quit_window(&win);
	return (0);
}
