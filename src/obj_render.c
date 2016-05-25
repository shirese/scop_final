/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 17:18:11 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/25 14:56:58 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void			transf_obj(t_obj **o)
{
	t_mat			*mat_test;
	t_mat			*mat_mvp;
	t_mat			*mat_rot;

	// compute_normals(o);
	mat_mvp = gen_mvp(o);
	mat_mvp->array[7] = 0.0f;
	// mat_mvp->array[7] = 0.0f;
	mat_rot = gen_rot_mat(o);
	mat_test = mat_mult(mat_mvp, mat_rot);
	gen_uniform_mat_4("mat_mvp", mat_test, (*o)->shader);
}

static void			gen_v_arr(t_obj *o)
{
	glBindBuffer(GL_ARRAY_BUFFER, o->vbo);
	glBindVertexArray(o->vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, o->vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, o->vnbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
}

void				render_obj(t_env *e)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(e->obj->shader);

	// Generate MVP + ROT
	transf_obj(&e->obj);

	gen_light(e->obj);

	gen_v_arr(e->obj);

	glDrawArrays (GL_TRIANGLE_FAN, 0, e->obj->p_count);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	// Swap buffers
	glfwSwapBuffers(e->win);
	glfwPollEvents();
}

void				init_rendering(t_obj **o)
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	// glEnable(GL_CULL_FACE);
	glGenVertexArrays(1, &(*o)->vao);
	glBindVertexArray((*o)->vao);
	// Init obj (set render var, load shaders)
	init_obj(o);
	// Load it into VBO
	init_vbo(o);
	init_vnbo(o);
	glUseProgram((*o)->shader);
	(*o)->light = glGetUniformLocation((*o)->shader, "light");
}
