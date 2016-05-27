/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_vertices.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 11:37:56 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/27 12:33:27 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void			triangulate(int *f, size_t *i, t_vec **v, float *ret)
{
	size_t			j;
	// f4 = v0 v2 v3
	j = *i;
	ret[++(*i)] = ret[j - 8];
	ret[++(*i)] = ret[j - 7];
	ret[++(*i)] = ret[j - 6];

	ret[++(*i)] = ret[j - 2];
	ret[++(*i)] = ret[j - 1];
	ret[++(*i)] = ret[j];

	ret[++(*i)] = v[*f - 1]->x;
	ret[++(*i)] = v[*f - 1]->y;
	ret[++(*i)] = v[*f - 1]->z;
}

void				compute_f_v(int *f, size_t *i, t_vec **v, float *ret)
{
	size_t			j;

	j = 0;
	while (*f != -1)
	{
		if (j > 2)
			triangulate(f, i, v, ret);
		else
		{
			ret[++(*i)] = v[*f - 1]->x;
			ret[++(*i)] = v[*f - 1]->y;
			ret[++(*i)] = v[*f - 1]->z;
		}
		f++;
		j++;
	}
}
