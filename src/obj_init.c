/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 10:46:28 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/24 18:02:03 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void			gen_light(t_obj **o)
{
	t_vec			*light;

	light = vec_new(4.0f, 4.0f, 4.0f);
	(*o)->light = glGetUniformLocation((*o)->shader, "light");
	glUniform3f((*o)->light, light->x, light->y, light->z);
	free(light);
}

static void			init_vnbo(t_obj **o)
{
	size_t			i;
	size_t			j;
	float			*vn;

	i = 0;
	j = 0;
	vn = NULL;
	while (i < (*o)->vn_size)
	{
		push('f', &(*o)->vn[i]->x, ++j, (void **)&vn);
		push('f', &(*o)->vn[i]->y, ++j, (void **)&vn);
		push('f', &(*o)->vn[i]->z, ++j, (void **)&vn);
		i++;
	}
	glGenBuffers(1, &(*o)->vnbo);
	glBindBuffer(GL_ARRAY_BUFFER, (*o)->vnbo);
	printf("==== VERTEX NORMALS ====\n");
	for (size_t z = 0; z < (*o)->vn_size; z++)
		printf("%f ", vn[i]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * i, &vn[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, (*o)->vnbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void				init_vbo(t_obj **o)
{
	size_t			i;
	size_t			j;
	int				*curr;
	float			*data;

	i = 0;
	j = -1;
	data = malloc(sizeof(float) * (*o)->p_count);
	while (i < (*o)->f_size)
	{
		curr = (*o)->f[i];
		while (*curr != -1)
		{
			data[++j] = (*o)->v[*curr - 1]->x;
			data[++j] = (*o)->v[*curr - 1]->y;
			data[++j] = (*o)->v[*curr - 1]->z;
			curr++;
		}
		i++;
	}
	glGenBuffers(1, &(*o)->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, (*o)->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (*o)->p_count, data, GL_STATIC_DRAW);
	free(data);
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
	(*o)->f_n = malloc(sizeof(t_vec *) * (*o)->f_size);
	if (!(*o)->vn)
	{
		compute_normals(o);
		init_vnbo(o);
	}
	(*o)->shader = load_shaders(VERTEX_SHADER, FRAG_SHADER);
	gen_light(o);
	mat_mvp = gen_mvp(o);
	// mat_mvp->array[7] = 0.0f;
	// mat_test = gen_trans_origin_mat(1, o);
	// mat_test2 = mat_mult(mat_mvp, mat_test);
	mat_rot = gen_rot_mat(o);
	mat_test = mat_mult(mat_mvp, mat_rot);
	// mat_test4 = gen_trans_origin_mat(0, o);
	// mat_test5 = mat_mult(mat_test3, mat_test4);
	gen_uniform_mat_4("mat_mvp", mat_test, (*o)->shader);
}
