/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 10:13:48 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/23 17:39:08 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void			destroy_obj(t_obj **o)
{
	if ((*o)->name)
		free((*o)->name);
	if ((*o)->lighting)
		free((*o)->lighting);
	if ((*o)->mtllib)
		free((*o)->mtllib);
	if ((*o)->mtl)
		free((*o)->mtl);
	free((*o)->v);
	free((*o)->v_index);
	if ((*o)->vn)
	{
		free((*o)->vn);
		free((*o)->vn_index);
	}
	if ((*o)->vt)
	{
		free((*o)->vt);
		free((*o)->vt_index);
	}
	free((*o)->f);
}

static int			init_env(t_env *e)
{
	if (!glfwInit())
		return (-1);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	e->win = glfwCreateWindow(W_W, W_H, e->obj->name, NULL, NULL);
	if (e->win == NULL)
	{
		glfwTerminate();
		return (-1);
	}
	glfwMakeContextCurrent(e->win);
	glfwSetInputMode(e->win, GLFW_STICKY_KEYS, GL_TRUE);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	return (1);
}

int					main(int ac, char **av)
{
	int				ret;
	t_env			env;

	ret = -1;
	if (ac == 2 && av[1])
	{
		if (parse_obj(av[1], &env.obj))
		{
			if (init_env(&env))
			{
				init_rendering(&env.obj);
				while (glfwGetKey(env.win, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
					glfwWindowShouldClose(env.win) == 0)
					render_obj(&env);
				// Cleanup VBO and shader
				glDeleteBuffers(1, &env.obj->vbo);
				// glDeleteBuffers(1, &env->vcolorbuffer);
				glDeleteProgram(env.obj->shader);
				glDeleteVertexArrays(1, &env.obj->vao);
				destroy_obj(&env.obj);
				// Close OpenGL window and terminate GLFW
				glfwTerminate();
			}
			else
				printf("Error while initializing environment\n");
		}
		else
			printf("Incorrect object file\n");
	}
	else
		printf("Usage ./scop [.obj]\n");
	return (ret);
}
