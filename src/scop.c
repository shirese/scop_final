/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 10:13:48 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/27 17:26:55 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void			destroy_obj(t_obj **o)
{
	if ((*o)->folder)
		free((*o)->folder);
	if ((*o)->name)
		free((*o)->name);
	while ((*o)->v_size--)
		free((*o)->v[(*o)->v_size]);
	free((*o)->v_index);
	while ((*o)->f_size--)
		free((*o)->f[(*o)->f_size]);
}

static int			init_env(t_env *e)
{
	if (!glfwInit())
		return (-1);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
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
		if (parse_obj(av[1], &env.obj) != -1)
		{
			// if (env.obj->mtllib)
			// {
			// 	if (parse_mtl_obj(&env.obj) == -1)
			// 	{
			// 		env.obj->mtl = NULL;
			// 		printf("Error while reading material file\n");
			// 		return (ret);
			// 	}
			// }
			print_obj(*env.obj);
			if (init_env(&env))
			{
				glfwSetKeyCallback(env.win, key_callback);
				init_rendering(&env.obj);
				while (glfwGetKey(env.win, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
					glfwWindowShouldClose(env.win) == 0)
					render_obj(&env);
				// Cleanup VBO and shader
				glDeleteBuffers(1, &env.obj->vbo);
				glDeleteBuffers(1, &env.obj->vco);
				// glDeleteBuffers(1, &env->vcolorbuffer);
				glDeleteProgram(env.obj->shader);
				glDeleteVertexArrays(1, &env.obj->vao);
				destroy_obj(&env.obj);
				// Close OpenGL window and terminate GLFW
				ret = 1;
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
