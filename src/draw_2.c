/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 16:08:49 by pribault          #+#    #+#             */
/*   Updated: 2017/03/29 17:10:55 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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

void	draw_debug(t_arena *arena, t_win *win)
{
	int		sqrt;
	int		i;
	int		j;

	win++;
	sqrt = ft_sqrt(MEM_SIZE);
	i = 0;
	ft_printf("cycle: %u\n", arena->cycle);
	while (i < sqrt)
	{
		j = 0;
		while (j < sqrt)
		{
			if (arena->territory[i * sqrt + j] / (MAX_PLAYERS + 1))
				ft_printf("\033[38;5;88m");
			else if (!arena->territory[i * sqrt + j])
				ft_printf("\033[38;5;240m");
			ft_printf("%.2hhx\033[0m ", arena->arena[i * sqrt + j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	ft_putchar('\n');
}
