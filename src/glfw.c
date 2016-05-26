/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 16:38:57 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/26 19:01:44 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static size_t		g_rot;
static char			g_rot_type = 'y';

void				key_callback(GLFWwindow* w, int k, int scode, int ac, int md)
{
	static int		wireframe = 0;

	if (w)
	{
		if (scode && md)
			;
		if ((k == GLFW_KEY_W || k == GLFW_KEY_D ) && ac == GLFW_PRESS)
		{
			if (wireframe != 1 && k == GLFW_KEY_W)
			{
				glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
				wireframe = 1;
			}
			else if (wireframe != 2 && k == GLFW_KEY_D)
			{
				glPolygonMode( GL_FRONT_AND_BACK, GL_POINT);
				wireframe = 2;
			}
			else
			{
				glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
				wireframe = 0;
			}
		}
		if (k == GLFW_KEY_R && ac == GLFW_PRESS)
		{
			if (!g_rot)
				g_rot = 1;
			else
				g_rot = 0;
		}
		if (k == GLFW_KEY_X && ac == GLFW_PRESS)
			g_rot_type = 'x';
		if (k == GLFW_KEY_Y && ac == GLFW_PRESS)
			g_rot_type = 'y';
		if (k == GLFW_KEY_Z && ac == GLFW_PRESS)
			g_rot_type = 'z';
	}
}

void				gen_rot(t_obj **o)
{
	(*o)->rot = g_rot;
	(*o)->rot_type = g_rot_type;
}
