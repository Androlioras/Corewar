/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 14:27:45 by pribault          #+#    #+#             */
/*   Updated: 2017/03/20 12:43:06 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_keys(t_win *win)
{
	if (win->events.window.event == SDL_WINDOWEVENT_CLOSE)
		win->stop = 1;
	if (win->events.key.keysym.sym == SDLK_ESCAPE)
		win->stop = 1;
	if (win->events.window.event == SDL_WINDOWEVENT_RESIZED)
		SDL_GetWindowSize(win->win, &(win->w), &(win->h));
}

void	print_map(t_arena *arena, t_win *win)
{
	float	v[8];
	double	diff;
	size_t	i[2];
	size_t	sq;

	arena++;
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
	sq = ft_sqrt(MEM_SIZE);
	diff = (double)2 / sq;
	i[0] = 0;
	while (i[0] < sq)
	{
		i[1] = 0;
		while (i[1] < sq)
		{
			v[0] = i[0] * diff - 1;
			v[1] = i[1] * diff - 1;
			v[2] = v[0] + diff;
			v[3] = v[1];
			v[4] = v[2];
			v[5] = v[1] + diff;
			v[6] = v[0];
			v[7] = v[5];
			printf("%f | %f\n", v[0], v[1]);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, v);
    		glDrawArrays(GL_QUADS, 0, 4);
    		glDisableVertexAttribArray(0);
			i[1]++;
		}
		i[0]++;
	}
    SDL_GL_SwapWindow(win->win);
}

int		must_print(void)
{
	static struct timeval	prev = {0, 0};
	static struct timeval	t;

	gettimeofday(&t, NULL);
	if ((t.tv_sec - prev.tv_sec) * 1000 + (t.tv_usec - prev.tv_usec) >= (double)1000 / MIN_FRAMERATE)
	{
		prev = t;
		return (1);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_arena	arena;
	t_win	win;

	arena.flags.flags = 0;
	arena.cycle = 0;
	win.name = "Corewar";
	win.w = 640;
	win.h = 480;
	win.stop = 0;
	ft_bzero(&arena.arena, MEM_SIZE);
	get_flags(&arena, argc, argv);
	init_window(&win);
	while (!win.stop)
	{
		if (SDL_PollEvent(&(win.events)))
			ft_keys(&win);
		virtual_machine(&arena);
		if (must_print())
			print_map(&arena, &win);
	}
	quit_window(&win);
	return (0);
}
