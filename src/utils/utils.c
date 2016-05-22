/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 11:11:14 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/20 17:40:39 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

float				centroid(char axis, float *f, size_t size)
{
	size_t			i;
	size_t			j;
	float			ret;

	// if axis = 'z' i = 2
	i = axis - 'x';
	j = 0;
	ret = 0;
	if (f != NULL)
	{
		while( i < size)
		{
			ret += f[i];
			i += 3;
			j++;
		}
	}
	ret /= j;
	return (ret);
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

void				get_face(t_obj **o)
{
	size_t			i;
	float			v[3];
	int				p_index;

	i = 0;
	while (i < (*o)->v_index_size)
	{
 		p_index = (*o)->v_index[i] * 3 - 3;
 		v[0] = (*o)->v[p_index];
 		v[1] = (*o)->v[p_index + 1];
 		v[2] = (*o)->v[p_index + 2];
		push('f', &v[0], ++(*o)->f_size, (void **)&(*o)->f);
		push('f', &v[1], ++(*o)->f_size, (void **)&(*o)->f);
		push('f', &v[2], ++(*o)->f_size, (void **)&(*o)->f);
		i++;
	}
}

void				print_obj(t_obj obj)
{
	size_t			i;

	i = 0;
	printf("==== OBJ %s ====\n", obj.name);
	printf("==== LIGHTING %s ====\n", obj.lighting);
	printf("==== MTLLIB %s ====\n", obj.mtllib);
	printf("==== MTL %s ====\n", obj.mtl);
	printf("==== VERTICES ====\n");
	while (i < obj.v_size)
	{
		if (i > 0 && i % 3 == 0)
			printf("\n");
		printf("V %f ", obj.v[i]);
		if (obj.vn)
			printf("VN %f ", obj.vn[i]);
		if (obj.vt)
			printf("VT %f", obj.vt[i]);
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
	printf("\n==== Points ====\n");
	printf("p ");
	while (i < obj.f_size)
	{
		if (i > 0 && i % 3 == 0)
			printf("\np ");
		printf("%f ", obj.f[i]);
		i++;
	}
}
