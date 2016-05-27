/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 10:46:28 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/27 18:03:44 by chaueur          ###   ########.fr       */
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

void				init_vbo(t_obj **o)
{
	size_t			i;
	size_t			j;
	float			*data;

	i = -1;
	j = -1;
	data = malloc(sizeof(float) * (*o)->p_count);
	while (++i < (*o)->f_size)
		compute_f_v((*o)->f[i], &j, (*o)->v, data);
	glGenBuffers(1, &(*o)->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, (*o)->vbo);
	printf("GEN VBO\n");
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (*o)->p_count, data, GL_STATIC_DRAW);
	// glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	free(data);
}

void				init_vco(t_obj **o)
{
	int				i;
	int				j;
	static float	val[3] = { 0.33f, 0.66f, 1.00f };
	float			*data;

	i = 0;
	printf("%d\n", (*o)->p_count);
	data = malloc(sizeof(float) * (*o)->p_count);
	while (i < (*o)->p_count / 9)
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (*o)->p_count, data, GL_STATIC_DRAW);
	// glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	free(data);
}

void				init_obj(t_obj **o)
{
	// (*o)->f_n = malloc(sizeof(t_vec *) * (*o)->f_size);
	// if (!(*o)->vn)
	// 	compute_normals(o);
	printf("=== gen vao ===\n");
	glGenVertexArrays(1, &(*o)->vao);
	glBindVertexArray((*o)->vao);
	init_vbo(o);
	init_vco(o);
	(*o)->rot_angle = 0;
	(*o)->rot_type = 'y';
	(*o)->shader = load_shaders(VERTEX_SHADER, FRAG_SHADER);
	// (*o)->textures = load_texture(o, )
}
