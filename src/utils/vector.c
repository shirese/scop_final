/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 18:06:38 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/24 12:29:40 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_vec				*vec_offset(t_vec *v1, t_vec *v2)
{
	t_vec			*v;

	v = vec_new(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
	return (v);
}
void				vec_rev(t_vec *v)
{
	v->x = -v->x;
	v->y = -v->y;
	v->z = -v->z;
}

float				vec_dot_prod(t_vec *v1, t_vec *v2)
{
	float			res;

	res = v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
	return (res);
}

t_vec				*vec_cross_prod(t_vec *v1, t_vec *v2)
{
	t_vec		*v;

	v = malloc(sizeof(t_vec));
	v->x = v1->y * v2->z - v1->z * v2->y;
	v->y = v1->z * v2->x - v1->x * v2->z;
	v->z = v1->x * v2->y - v1->y * v2->x;
	return (v);
}

void				vec_normalize(t_vec *v)
{
	float		v_len;

	v_len = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	if (v_len)
	{
		v->x /= v_len;
		v->y /= v_len;
		v->z /= v_len;
	}
}

t_vec				*vec_new(float x, float y, float z)
{
	t_vec		*v;

	v = malloc(sizeof(t_vec));
	v->x = x;
	v->y = y;
	v->z = z;
	return (v);
}
