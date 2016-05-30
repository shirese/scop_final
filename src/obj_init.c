/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 10:46:28 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/30 16:22:43 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void				init_light_env(t_light **l, GLuint *shader)
{
	(*l) = malloc(sizeof(t_light));
	(*l)->light = 0.0f;
	(*l)->diff = 0.0f;
	(*l)->spec = 0.0f;
	(*l)->ambiant = 0.0f;
	printf("\nLOC LIGHT %d\n", (*l)->light);
	(*l)->light = glGetUniformLocation(*shader, "light");
	printf("\nLOC LIGHT %d\n", (*l)->light);
	(*l)->diff = glGetUniformLocation(*shader, "diffuse");
	printf("LOC DIFF %d\n", (*l)->diff);
	(*l)->spec = glGetUniformLocation(*shader, "spec");
	printf("LOC SPEC %d\n", (*l)->spec);
	(*l)->ambiant = glGetUniformLocation(*shader, "ambiant");
	printf("LOC AMBIANT %d\n", (*l)->ambiant);
}

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

void				init_uv(t_obj **o)
{
	gen_uv(o);
	glGenBuffers(1, &(*o)->uv);
	glBindBuffer(GL_ARRAY_BUFFER, (*o)->uv);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (*o)->p_size, (*o)->uv_data, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
}

void				init_vbo(t_obj **o)
{
	size_t			i;
	size_t			j;

	i = -1;
	j = -1;
	(*o)->p = malloc(sizeof(float) * (*o)->p_size);
	while (++i < (*o)->f_size)
		compute_f_v((*o)->f[i], &j, (*o)->v, (*o)->p);
	glGenBuffers(1, &(*o)->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, (*o)->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (*o)->p_size, (*o)->p, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
}

void				init_vco(t_obj **o)
{
	int				i;
	int				j;
	static float	val[3] = { 0.33f, 0.66f, 1.00f };
	float			*data;

	i = 0;
	printf("VCO\n");
	printf("%d\n", (*o)->p_size);
	data = malloc(sizeof(float) * (*o)->p_size);
	while (i < (*o)->p_size / 9)
	{
		j = 0;
		while (j < 9)
		{
			data[i * 9 + j] = val[i % 3];
			j++;
		}
		i++;
	}
	glGenBuffers(1, &(*o)->vco);
	glBindBuffer(GL_ARRAY_BUFFER, (*o)->vco);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (*o)->p_size, data, GL_STATIC_DRAW);
	// glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	free(data);
}

void				init_obj(t_obj **o)
{
	// (*o)->f_n = malloc(sizeof(t_vec *) * (*o)->f_size);
	// if (!(*o)->vn)
	// 	compute_normals(o);
	find_center(o);
	vec_rev((*o)->center);
	glGenVertexArrays(1, &(*o)->vao);
	glBindVertexArray((*o)->vao);
	(*o)->rot_angle = 0;
	(*o)->rot_type = 'y';
	(*o)->shader = load_shaders(VERTEX_SHADER, FRAG_SHADER);
	(*o)->tex = 0;
	load_texture(TEXTURE_FILE, o);
	// (*o)->textures = load_texture(o, )
}
