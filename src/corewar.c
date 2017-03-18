/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 14:27:45 by pribault          #+#    #+#             */
/*   Updated: 2017/03/18 16:41:05 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void renderScene(void)
{
	char	*n;
	int		i;
	int		l;

	n = ft_itoa(glutGet(GLUT_ELAPSED_TIME) / 1000);
	glRasterPos2f(0, 0);
	i = 0;
	l = ft_strlen(n);
	while (i < l)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, n[i++]);
	free(n);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_POLYGON);
		glVertex3f(-0.5,-0.5,0.0);
		glVertex3f(0.5,0.0,0.0);
		glVertex3f(0.0,0.5,0.0);
		glVertex3f(-0.5,0.5,0.0);
	glEnd();
    glutSwapBuffers();
}

int		main(int argc, char **argv)
{
	t_arena	arena;
	t_win	win;

	arena.flags.flags = 0;
	arena.cycle = 0;
	win.name = "Corewar";
	win.w = 1920;
	win.h = 1080;
	ft_bzero(&arena.arena, MEM_SIZE);
	get_flags(&arena, argc, argv);
	ft_printf("champion 1: %u\n", ((t_process*)arena.champs[0].process->content)->reg[0]);
	init_window(&win, &argc, argv);
	glutDisplayFunc(renderScene);
	glutMainLoop();
	virtual_machine(&arena);
	return (0);
}
