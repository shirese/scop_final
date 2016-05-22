/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 15:37:47 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/22 15:22:16 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_mat				*mat_identity(void)
{
	int				i;
	t_mat			*m_i;

	i = 1;
	m_i = mat_new(4, 4);
	mat_zero(m_i);

	while (i <= m_i->width)
	{
		mat_set(m_i, i, i, 1.0f);
		i++;
	}
	return m_i;
}

static void			mat_mult_comp(t_mat *m1, t_mat *m2, t_mat *res, int m_ind)
{
	int				x_m[2];
	int				y_m[2];
	float			tmp;

	y_m[0] = 0;
	while (++y_m[0] <= m1->height)
	{
		x_m[1] = 0;
		while (++x_m[1] <= m2->width)
		{
			tmp = 0.000000f;
			y_m[1] = 0;
			while (++y_m[1] <= m2->height)
				tmp += m1->array[m1->width * (y_m[0] - 1) + y_m[1] - 1] * m2->array[x_m[1] + (y_m[1] - 1) * m2->width - 1];
			res->array[m_ind++] = tmp;
		}
	}
}

t_mat				*mat_mult(t_mat *m1, t_mat *m2)
{
	t_mat			*res;
	int				mat_index;

	if (m1->width != m2->height)
		return NULL;
	res = mat_new(m2->width, m1->height);
	mat_zero(res);
	mat_index = 0;
	mat_mult_comp(m1, m2, res, mat_index);
	return res;
}


t_mat				*mat_new(int width, int height)
{
	t_mat			*mat;

	mat = malloc(sizeof(t_mat));
	mat->array = malloc(width * height * sizeof(float));
	mat->width = width;
	mat->height = height;
	return (mat);
}

void				mat_zero(t_mat *dest)
{
	bzero(dest->array, dest->width * dest->height * sizeof(float));
}
