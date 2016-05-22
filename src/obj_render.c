/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 17:18:11 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/22 18:38:39 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void			gen_uniform_mat_4(char *name, t_mat *mat, GLuint shader)
{
	float			*f_mvp;
	GLuint			m_id;

	print_mat(mat);
	f_mvp = mat_to_float(mat);
	m_id = glGetUniformLocation(shader, name);
	glUniformMatrix4fv(m_id, 1, GL_FALSE, &f_mvp[0]);
}

static void			init_obj(t_obj *o)
{
	t_mat			*mat_test;
	t_mat			*mat_mvp;
	t_mat			*mat_rot;

	if (!o->rot)
		o->rot = 0.0f;
	if (!o->rot_type)
		o->rot_type = 'y';
	if (!o->shader)
		o->shader = load_shaders("shaders/vertex_shader", "shaders/fragment_shader");
	mat_mvp = gen_mvp();
	// mat_mvp->array[7] = 0.0f;
	// mat_test = gen_trans_origin_mat(1, o);
	// mat_test2 = mat_mult(mat_mvp, mat_test);
	mat_rot = gen_rot_mat(o);
	mat_test = mat_mult(mat_mvp, mat_rot);
	// mat_test4 = gen_trans_origin_mat(0, o);
	// mat_test5 = mat_mult(mat_test3, mat_test4);
	gen_uniform_mat_4("mat_mvp", mat_test, o->shader);
	glUseProgram (o->shader);
}

static void				init_vbo(t_obj *o)
{
	glGenBuffers(1, &o->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, o->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * o->f_size, o->f, GL_STATIC_DRAW);
}

static void				init_vao(t_obj *o)
{
	glGenVertexArrays(1, &o->vao);
	glBindVertexArray(o->vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, o->vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void				render_obj(t_env *e)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Enable depth test
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);	
	init_obj(e->obj);
	e->obj->rot += 0.1f;
	init_vbo(e->obj);
	init_vao(e->obj);
	glBindVertexArray (e->obj->vao);
	// Render num face * 3 vertex
	glDrawArrays (GL_TRIANGLE_FAN, 0, e->obj->f_size * 3);
	// render points 0-3 from the currently bound VAO with current in-use shader
	glDisableVertexAttribArray(0);

	// Swap buffers
	glfwSwapBuffers(e->win);
	glfwPollEvents();
}
