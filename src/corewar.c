/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ardanel <ardanel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 14:27:45 by pribault          #+#    #+#             */
/*   Updated: 2017/03/18 22:50:43 by ardanel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
	
t_arena	arena;
t_win	win;

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnd();
    glutSwapBuffers();
}

void	corewar(void)
{
	virtual_machine(&arena);
}

void    event_keys(t_char key, int x, int y)
{
    x++;
    y++;
    ft_printf("key %hhu pressed\n", key);
    if (key == 27)
        exit(0);
}

int		main(int argc, char **argv)
{

	arena.flags.flags = 0;
	arena.cycle = 0;
	win.name = "Corewar";
	win.w = 640;
	win.h = 480;
	ft_bzero(&arena.arena, MEM_SIZE);
	get_flags(&arena, argc, argv);
	init_window(&win, &argc, argv);
	ft_printf("champion 1: %u\n", ((t_process*)arena.champs[0].process->content)->reg[0]);
	glutDisplayFunc(renderScene);
	glutIdleFunc(corewar);
    glutKeyboardFunc(event_keys);
	glutMainLoop();
	return (0);
}
