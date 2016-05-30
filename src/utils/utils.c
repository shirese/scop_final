/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 11:11:14 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/30 17:29:55 by chaueur          ###   ########.fr       */
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
	printf("%f %f\n", max_xy[0], min_xy[0]);
	(*o)->k[0] = 1 / (max_xy[1] - min_xy[0]);
	(*o)->k[1] = 1 / (max_xy[0] - min_xy[1]);
	printf("%f\n", (*o)->k[0]);
	printf("%f\n", (*o)->k[1]);
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

void				print_obj(t_obj obj)
{
	size_t			i;

	i = 0;
	printf("==== FOLDER %s ====\n", obj.folder);
	printf("==== OBJ %s ====\n", obj.name);
	printf("==== LIGHTING %s ====\n", obj.lighting);
	if (obj.mtllib && obj.mtl)
	{
		printf("==== MTLLIB %s ====\n", obj.mtllib);
		printf("==== MTL %s ====\n", obj.mtl_name);
		printf("%f\n", obj.mtl->ns);
		printf("%f %f %f\n", obj.mtl->ka->x, obj.mtl->ka->y, obj.mtl->ka->z);
		printf("%f %f %f\n", obj.mtl->kd->x, obj.mtl->kd->y, obj.mtl->kd->z);
		printf("%f %f %f\n", obj.mtl->ks->x, obj.mtl->ks->y, obj.mtl->ks->z);
		printf("%f\n", obj.mtl->ni);
		printf("%f\n", obj.mtl->d);
		printf("%zu\n", obj.mtl->illum);
	}
	printf("==== VERTICES ====\n");
	while (i < obj.v_size)
	{
		printf("%f %f %f\n", obj.v[i]->x, obj.v[i]->y, obj.v[i]->z);
		i++;
	}
	printf("==== P COUNT %d ====\n", obj.p_size);
	printf("==== FACES ====\n");
	i = 0;
	while (i < obj.f_size)
	{
		printf("f");
		int *tmp = NULL;
		tmp = obj.f[i];
		while (*tmp != -1)
		{
			printf(" %d", *tmp);
			tmp++;
		}
		printf("\n");
		i++;
	}
	// i = 0;
	// printf("\n==== FACES ====\n");
	// printf("f ");
	// while (i < obj.v_index_size)
	// {
	// 	if (i > 0 && i % 3 == 0)
	// 		printf("\nf ");
	// 	printf("%d ", obj.v_index[i]);
	// 	i++;
	// }
	i = 0;
	// printf("\n==== Points ====\n");
	// printf("p ");
	// while (i < (int)obj.p_size)
	// {
	// 	int j = 0;
	// 	int f = 0;
	// 	while (j != -1)
	// 		printf("%f ", obj.f[f++][j]);
	// 	i++;
	// }
}
