/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 10:46:28 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/31 18:45:49 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void				init_vnbo(t_obj **o)
{
	size_t			i;
	size_t			j;
	size_t			v_index;
	float			*vn;

	i = 0;
	j = 0;
	v_index = 0;
	vn = NULL;
	while (i < (*o)->f_size)
	{
		while (*(*o)->f[i] != -1)
		{
			v_index = *(*o)->f[i];
			push('f', &(*o)->vn[v_index - 1]->x, ++j, (void **)&vn);
			push('f', &(*o)->vn[v_index - 1]->y, ++j, (void **)&vn);
			push('f', &(*o)->vn[v_index - 1]->z, ++j, (void **)&vn);
			(*o)->f[i]++;
		}
		i++;
	}
	glGenBuffers(1, &(*o)->vnbo);
	glBindBuffer(GL_ARRAY_BUFFER, (*o)->vnbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * j, vn, GL_STATIC_DRAW);
	free(vn);
}

void				init_uv(t_obj **o)
{
	float			size;

	size = sizeof(float) * (*o)->p_size;
	gen_uv(o);
	glGenBuffers(1, &(*o)->uv);
	glBindBuffer(GL_ARRAY_BUFFER, (*o)->uv);
	glBufferData(GL_ARRAY_BUFFER, size, (*o)->uv_data, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
}

void				init_vbo(t_obj **o)
{
	size_t			i;
	size_t			j;
	float			size;

	i = -1;
	j = -1;
	size = sizeof(float) * (*o)->p_size;
	(*o)->p = malloc(size);
	while (++i < (*o)->f_size)
		compute_f_v((*o)->f[i], &j, (*o)->v, (*o)->p);
	glGenBuffers(1, &(*o)->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, (*o)->vbo);
	glBufferData(GL_ARRAY_BUFFER, size, (*o)->p, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
}

void				init_vco(t_obj **o)
{
	int				i[2];
	static float	val[3] = { 0.33f, 0.66f, 1.00f };
	float			size;
	float			*data;

	i[0] = 0;
	size = sizeof(float) * (*o)->p_size;
	data = malloc(size);
	while (i[0] < (*o)->p_size / 9)
	{
		i[1] = 0;
		while (i[1] < 9)
		{
			data[i[0] * 9 + i[1]] = val[i[0] % 3];
			i[1]++;
		}
		i[0]++;
	}
	glGenBuffers(1, &(*o)->vco);
	glBindBuffer(GL_ARRAY_BUFFER, (*o)->vco);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	free(data);
}

void				init_obj(t_obj **o)
{
	rescale_v(o);
	find_center(o);
	vec_rev((*o)->center);
	glGenVertexArrays(1, &(*o)->vao);
	glBindVertexArray((*o)->vao);
	(*o)->rot_angle = 0;
	(*o)->rot_type = 'y';
	(*o)->shader = load_shaders(VERTEX_SHADER, FRAG_SHADER);
	(*o)->tex = 0;
	load_texture(TEXTURE_FILE, o);
}
