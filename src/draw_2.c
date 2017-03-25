/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 16:08:49 by pribault          #+#    #+#             */
/*   Updated: 2017/03/25 16:40:29 by pribault         ###   ########.fr       */
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
