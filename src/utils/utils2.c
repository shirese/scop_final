/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 18:22:07 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/31 18:58:52 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void				rescale_v(t_obj **o)
{
	size_t			i;
	float			max;

	i = -1;
	max = 0.0f;
	while (++i < (*o)->v_size)
	{
		if (max < (*o)->v[i]->x)
			max = (*o)->v[i]->x;
		if (max < (*o)->v[i]->y)
			max = (*o)->v[i]->y;
		if (max < (*o)->v[i]->z)
			max = (*o)->v[i]->z;
		i++;
	}
	if (max >= 10.0f && (max /= 5.0f))
	{
		i = -1;
		while (++i < (*o)->v_size)
		{
			(*o)->v[i]->x /= max;
			(*o)->v[i]->y /= max;
			(*o)->v[i]->z /= max;
		}
	}
}
