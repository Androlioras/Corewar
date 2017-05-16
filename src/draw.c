/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 13:04:54 by pribault          #+#    #+#             */
/*   Updated: 2017/05/16 11:59:24 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

SDL_Texture	*define_color(t_arena *arena, t_win *win, int i)
{
	t_char		player;
	t_char		value;

	player = arena->territory[i];
	value = arena->arena[i];
	return (win->textures[player * 0x100 + value]);
}

void		draw_arena(t_arena *arena, t_win *win, int arena_size)
{
	SDL_Rect	rect;
	double		diff;
	int			sqrt;
	int			i;
	int			j;

	sqrt = ft_sqrt(MEM_SIZE);
	diff = (double)arena_size / sqrt;
	rect.w = diff - 2;
	rect.h = diff - 2;
	i = 0;
	while (i < sqrt)
	{
		j = 0;
		rect.y = i * diff + 1;
		while (j < sqrt)
		{
			rect.x = j * diff + 1;
			SDL_RenderCopy(win->render, define_color(arena, win, i * sqrt + j),
			NULL, &rect);
			j++;
		}
		i++;
	}
}

void		print_fps(t_win *win)
{
	static struct timeval	prev;
	static struct timeval	t;
	static t_char			count;
	int						fps;
	char					*s;

	gettimeofday(&t, NULL);
	if (count++ >= 60)
	{
		fps = 1000000 * (t.tv_sec - prev.tv_sec);
		if (fps + t.tv_usec - prev.tv_usec != 0)
			fps = 1000000 / (fps + t.tv_usec - prev.tv_usec);
		else
			fps = MIN_FRAMERATE;
		s = ft_joinf("%s | fps:%d", win->name, fps);
		SDL_SetWindowTitle(win->win, s);
		free(s);
		count = 0;
	}
	prev = t;
}

void		print_panel(t_arena *arena, t_win *win, int arena_size)
{
	SDL_Color	color;
	SDL_Rect	rect;
	char		*s;

	rect.x = arena_size + 10;
	rect.y = 20;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 0;
	s = ft_joinf("cycle: %d", arena->cycle);
	rect.w = win->w - arena_size - 20;
	rect.h = rect.w / ft_strlen(s);
	print_text(win, s, &rect, &color);
	free(s);
	rect.y += rect.h + 20;
	rect.h = rect.w / ft_strlen(s);
	s = ft_joinf("speed: %d/sec", arena->speed);
	print_text(win, s, &rect, &color);
	free(s);
	rect.y += rect.h + 20;
	rect.h = rect.w / ft_strlen(s);
	s = ft_joinf("cycle to die: %d", arena->cycle_to_die);
	print_text(win, s, &rect, &color);
	free(s);
}

void		print_map(t_arena *arena, t_win *win)
{
	SDL_Rect		rect;
	int				arena_size;

	arena_size = (win->w > win->h) ? win->h : win->w;
	print_fps(win);
	SDL_SetRenderDrawColor(win->render, 0, 0, 0, 0);
	SDL_RenderClear(win->render);
	rect.w = arena_size;
	rect.h = arena_size;
	rect.x = 0;
	rect.y = 0;
	SDL_SetRenderDrawColor(win->render, 192, 192, 192, 0);
	SDL_RenderDrawRect(win->render, &rect);
	draw_arena(arena, win, arena_size - 2);
	print_panel(arena, win, arena_size);
	SDL_RenderPresent(win->render);
}
