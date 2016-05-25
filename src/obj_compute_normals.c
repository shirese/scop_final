/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_compute_normals.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 10:45:27 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/25 11:39:12 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_vec				*average_normals(t_vec *v1, t_vec *v2)
{
	v1->x = (v1->x - v2->x) / 2;
	v1->y = (v1->y - v2->y) / 2;
	v1->z = (v1->z - v2->z) / 2;
	return (v1);
}

t_vec				*compute_f_normal(int *f, t_obj **o)
{
	size_t			i;
	t_vec			v[4];
	t_vec			**offset;
	t_vec			**vn;

	i = -1;
	v[3].x = 0;
	while (*f != -1)
	{
		v[++i] = *(*o)->v[*f - 1];
		f++;
	}
	vn = malloc(sizeof(t_vec *) * ((i + 1) / 2));
	offset = malloc(sizeof(t_vec *) * 2);
	offset[0] = vec_offset(&v[2], &v[0]);
	offset[1] = vec_offset(&v[0], &v[1]);
	vn[0] = vec_cross_prod(offset[0], offset[1]);
	if (v[3].x)
	{
		offset[0] = vec_offset(&v[2], &v[3]);
		offset[1] = vec_offset(&v[0], &v[3]);
		vn[1] = vec_cross_prod(offset[0], offset[1]);
		vn[0] = average_normals(vn[0], vn[1]);
		free(vn[1]);
	}
	vec_normalize(vn[0]);
	free(offset[0]);
	free(offset[1]);
	return (vn[0]);
}

t_vec				*avg_v(int *f, t_obj *o)
{
	size_t			n_adj_f;
	t_vec			*v;
	t_vec			*v_f;

	n_adj_f = 0;
	v = malloc(sizeof(t_vec));
	while (*f != -1)
	{
		v_f = o->v[*f - 1];
		v->x += v_f->x;
		v->y += v_f->y;
		v->z += v_f->z;
		n_adj_f++;
		f++;
	}
	v->x /= n_adj_f;
	v->y /= n_adj_f;
	v->z /= n_adj_f;
	return (v);
}

void				check_adj_f(t_vec *v, t_obj *o, int **f_adj)
{
	size_t			i;
	size_t			size;
	int				*f;
	t_vec			*v_f;

	i = 0;
	size = 0;
	while (i < o->f_size)
	{
		f = o->f[i];
		while (*f != -1)
		{
			v_f = o->v[*f - 1];
			if (v_f->x == v->x && v_f->y == v->y && v_f->z == v->z)
				push('i', f, ++size, (void **)f_adj);
			f++;
		}
		i++;
	}
	i = -1;
	push('i', &i, ++size, (void **)f_adj);
}

void				compute_normals(t_obj **o)
{
	size_t			i;
	int				*f_adj;
	t_vec			*v;

	i = 0;
	while (i < (*o)->f_size)
	{
		(*o)->f_n[i] = compute_f_normal((*o)->f[i], o);
		i++;
	}
	i = 0;
	(*o)->vn = NULL;
	(*o)->vn_size = 0;
	while (i < (*o)->v_size)
	{
		f_adj = NULL;
		check_adj_f((*o)->v[i], *o, &f_adj);
		v = avg_v(f_adj, *o);
		vec_normalize(v);
		push_vec(*v, ++(*o)->vn_size, &(*o)->vn);
		free(v);
		i++;
	}
}
