/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 10:46:28 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/25 12:39:19 by chaueur          ###   ########.fr       */
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
	printf("==== VN ====\n");
	for (size_t z = 0; z < j; z++)
	{
		if (z && z % 3 == 0)
			printf("\n");
		printf("%f ", vn[z]);
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * j, vn, GL_STATIC_DRAW);
	free(vn);
}

void				gen_light(t_obj *o)
{
	t_vec			*light;

	light = vec_new(4.0f, 4.0f, 4.0f);
	glUniform3f(o->light, light->x, light->y, light->z);
	free(light);
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

void				init_obj(t_obj **o)
{
	(*o)->rot = 0.0f;
	(*o)->rot_type = 'y';
	(*o)->f_n = malloc(sizeof(t_vec *) * (*o)->f_size);
	if (!(*o)->vn)
		compute_normals(o);
	(*o)->shader = load_shaders(VERTEX_SHADER, FRAG_SHADER);
}
