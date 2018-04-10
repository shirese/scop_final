/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 11:11:14 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/31 18:26:18 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void				find_texture_space(t_obj **o)
{
	size_t			i;
	double			min_xy[2];
	double			max_xy[2];

	i = (*o)->v_size - 1;
	min_xy[0] = (*o)->v[i]->x;
	min_xy[1] = (*o)->v[i]->y;
	memcpy(max_xy, min_xy, 2);
	while (i--)
	{
		min_xy[0] = fmin((*o)->v[i]->x, min_xy[0]);
		min_xy[1] = fmin((*o)->v[i]->y, min_xy[1]);
		max_xy[0] = fmax((*o)->v[i]->x, max_xy[0]);
		max_xy[1] = fmax((*o)->v[i]->y, max_xy[1]);
	}
	(*o)->k = malloc(sizeof(double) * 2);
	(*o)->k[0] = 1 / (max_xy[1] - min_xy[0]);
	(*o)->k[1] = 1 / (max_xy[0] - min_xy[1]);
}

void				find_center(t_obj **o)
{
	size_t			i;
	double			min_xyz[3];
	double			max_xyz[3];
	t_vec			*c;

	i = (*o)->v_size - 1;
	min_xyz[0] = (*o)->v[i]->x;
	min_xyz[1] = (*o)->v[i]->y;
	min_xyz[2] = (*o)->v[i]->z;
	memcpy(max_xyz, min_xyz, 3);
	while (i--)
	{
		min_xyz[0] = fmin((*o)->v[i]->x, min_xyz[0]);
		min_xyz[1] = fmin((*o)->v[i]->y, min_xyz[1]);
		min_xyz[2] = fmin((*o)->v[i]->z, min_xyz[2]);
		max_xyz[0] = fmax((*o)->v[i]->x, max_xyz[0]);
		max_xyz[1] = fmax((*o)->v[i]->y, max_xyz[1]);
		max_xyz[2] = fmax((*o)->v[i]->z, max_xyz[2]);
	}
	c = malloc(sizeof(t_vec));
	c->x = (float)((min_xyz[0] + max_xyz[0]) / 2);
	c->y = (float)((min_xyz[1] + max_xyz[1]) / 2);
	c->z = (float)((min_xyz[2] + max_xyz[2]) / 2);
	(*o)->center = c;
}

void				print_mat(t_mat *m)
{
	int				i;
	int				size;

	i = 1;
	size = m->width * m->height;
	printf("\n");
	while (i <= size)
	{
		printf("%f ", m->array[i - 1]);
		if (i % m->width == 0)
			printf("\n");
		i++;
	}
}

void				push(char type, void *val, size_t i, void **arr)
{
	float			*f;
	int				*j;

	if (type == 'f')
	{
		*arr = realloc(*arr, sizeof(float) * i);
		f = *arr;
		f[i - 1] = *((float *)val);
	}
	else if (type == 'i')
	{
		*arr = realloc(*arr, sizeof(int) * i);
		j = *arr;
		j[i - 1] = *((int *)val);
	}
}

void				push_vec(t_vec v, size_t size, t_vec ***v_arr)
{
	*v_arr = realloc(*v_arr, sizeof(t_vec *) * size);
	(*v_arr)[size - 1] = malloc(sizeof(t_vec));
	(*v_arr)[size - 1]->x = v.x;
	(*v_arr)[size - 1]->y = v.y;
	(*v_arr)[size - 1]->z = v.z;
}
