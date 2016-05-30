/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 16:38:57 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/30 18:46:51 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static size_t		g_rot;
static size_t		g_rot_clockwise = 1;
static char			g_rot_type = 'y';
static char			g_fade_out = -1;

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
		if (k == GLFW_KEY_B && ac == GLFW_PRESS)
			g_rot_clockwise *= -1;
		if (k == GLFW_KEY_T && ac == GLFW_PRESS)
			g_fade_out *= -1;
	}
}

void				gen_rot(t_obj **o)
{
	(*o)->rot = g_rot;
	(*o)->rot_clockwise = g_rot_clockwise;
	(*o)->rot_type = g_rot_type;
}

void				gen_fade(t_obj *o)
{
	static float	a1_val;
	static float	a2_val;
	static int		init;

	GLuint			a1;
	GLuint			a2;
	a1 = glGetUniformLocation(o->shader, "alpha1");
	a2 = glGetUniformLocation(o->shader, "alpha2");
	if (!init)
	{
		init = 1;
		a1_val = 1.0f;
		a2_val = 0.0f;
	}
	if (g_fade_out == 1)
	{
		if (a1_val >= 0.0f)
			a1_val -= 0.01f;
		if (a2_val <= 1.0f)
			a2_val += 0.01f;

	}
	else if (g_fade_out == -1)
	{
		if (a2_val >= 0.0f)
			a2_val -= 0.01f;
		if (a1_val <= 1.0f)
			a1_val += 0.01f;
	}
	glUniform1f(a1, a1_val);
	glUniform1f(a2, a2_val);
}
