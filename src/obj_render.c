/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 17:18:11 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/24 15:14:03 by chaueur          ###   ########.fr       */
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

void				render_obj(t_env *e)
{
	transf_obj(&e->obj);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Enable depth test
	glClearDepth(1.0f);
	// Vertices
	glUseProgram(e->obj->shader);
	glBindBuffer(GL_ARRAY_BUFFER, e->obj->vbo);
	glBindVertexArray(e->obj->vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, e->obj->vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// UNSURE
	glBindVertexArray (e->obj->vao);

	glDrawArrays (GL_TRIANGLE_FAN, 0, e->obj->f_size * 3);
	glDisableVertexAttribArray(0);
	// Swap buffers
	glfwSwapBuffers(e->win);
	glfwPollEvents();
}

void				init_rendering(t_obj **o)
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	init_obj(o);
	init_vbo(o);
	init_vao(o);
}
