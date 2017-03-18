/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 09:13:13 by pribault          #+#    #+#             */
/*   Updated: 2017/03/18 09:39:13 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init_window(t_win *win, int *argc, char **argv)
{
	win->w = (win->w > WIN_W_SIZE) ? WIN_W_SIZE : win->w;
	win->h = (win->h > WIN_H_SIZE) ? WIN_H_SIZE : win->h;
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition((WIN_W_SIZE - win->w) / 2, 100);
	glutInitWindowSize(win->w, win->h);
	glutCreateWindow(win->name);
}
