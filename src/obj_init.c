/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 10:46:28 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/23 18:17:49 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void				init_vbo(t_obj **o)
{
	glGenBuffers(1, &(*o)->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, (*o)->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (*o)->f_size, (*o)->f, GL_STATIC_DRAW);
}

void				init_vao(t_obj **o)
{
	glGenVertexArrays(1, &(*o)->vao);
	glBindVertexArray((*o)->vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, (*o)->vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void				init_obj(t_obj **o)
{
	t_mat			*mat_test;
	t_mat			*mat_mvp;
	t_mat			*mat_rot;

	(*o)->rot = 0.0f;
	(*o)->rot_type = 'y';
	(*o)->shader = load_shaders("shaders/vertex_shader", "shaders/fragment_shader");
	(*o)->f_n = NULL;
	// compute_normals(o);
	mat_mvp = gen_mvp();
	// mat_mvp->array[7] = 0.0f;
	// mat_test = gen_trans_origin_mat(1, o);
	// mat_test2 = mat_mult(mat_mvp, mat_test);
	mat_rot = gen_rot_mat(o);
	mat_test = mat_mult(mat_mvp, mat_rot);
	// mat_test4 = gen_trans_origin_mat(0, o);
	// mat_test5 = mat_mult(mat_test3, mat_test4);
	gen_uniform_mat_4("mat_mvp", mat_test, (*o)->shader);
}
