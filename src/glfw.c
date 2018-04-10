/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 16:38:57 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/31 19:31:19 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static size_t		g_rot;
static size_t		g_rot_clockwise = 1;
static char			g_rot_type = 'y';
static char			g_fade_out = -1;
static float		g_scale = 1.0f;
static float		g_x = 0.0f;
static float		g_y = 0.0f;
static float		g_z = 0.0f;
void				key_callback(GLFWwindow *w, int k, int scode, int ac, int md)
{
	static int		wireframe = 0;

	if (w)
	{
		if (scode && md)
			;
		if ((k == GLFW_KEY_W || k == GLFW_KEY_D) && ac == GLFW_PRESS)
		{
			if (wireframe != 1 && k == GLFW_KEY_W)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				wireframe = 1;
			}
			else if (wireframe != 2 && k == GLFW_KEY_D)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
				wireframe = 2;
			}
			else
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
		if (k == GLFW_KEY_MINUS && ac == GLFW_REPEAT)
		{
			if (g_scale > 0.0f)
				g_scale -= 0.05f;
		}
		if (k == GLFW_KEY_EQUAL && ac == GLFW_REPEAT)
		{
			if (g_scale < 1.0f)
				g_scale += 0.05f;
		}
		if (k == GLFW_KEY_KP_1 && ac == GLFW_REPEAT)
			g_x += 0.05f;
		if (k == GLFW_KEY_KP_9 && ac == GLFW_REPEAT)
			g_x -= 0.05f;
		if (k == GLFW_KEY_KP_2 && ac == GLFW_REPEAT)
			g_y -= 0.05f;
		if (k == GLFW_KEY_KP_8 && ac == GLFW_REPEAT)
			g_y += 0.05f;
		if (k == GLFW_KEY_KP_7 && ac == GLFW_REPEAT)
			g_z += 0.05f;
		if (k == GLFW_KEY_KP_3 && ac == GLFW_REPEAT)
			g_z -= 0.05f;
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
	static int		init;
	static float	a_val[2];
	GLuint			a[2];
	float			val;

	a[0] = glGetUniformLocation(o->shader, "alpha1");
	a[1] = glGetUniformLocation(o->shader, "alpha2");
	if (!init)
	{
		init = 1;
		a_val[0] = 1.0f;
		a_val[1] = 0.0f;
		val = 0.0f;
	}
	if (g_fade_out == 1)
		val = 0.01f;
	else
		val = -0.01f;
	if (a_val[0] - val >= 0.0f && a_val[0] - val <= 1.0f)
		a_val[0] -= val;
	if (a_val[1] + val >= 0.0f && a_val[1] + val <= 1.0f)
		a_val[1] += val;
	glUniform1f(a[0], a_val[0]);
	glUniform1f(a[1], a_val[1]);
}

void				gen_scale(t_obj *o)
{
	GLuint			scale;

	if (g_scale >= 0.0f)
	{
		scale = glGetUniformLocation(o->shader, "scale");
		glUniform1f(scale, g_scale);
	}
}

t_vec				gen_trans(t_obj *o)
{
	GLuint			trans;
	t_vec			t;

	t.x = g_x;
	t.y = g_y;
	t.z = g_z;
	trans = glGetUniformLocation(o->shader, "trans");
	glUniform3f(trans, t.x, t.y, t.z);
	return (t);
}
