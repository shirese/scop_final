/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 13:04:09 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/27 13:22:40 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static t_mat		*mat_rot_x(float ang)
{
	t_mat			*mat_rot;

	mat_rot = mat_new(4, 4);
	mat_zero(mat_rot);
	mat_set(mat_rot, 1, 1, 1.0f);
	mat_set(mat_rot, 4, 4, 1.0f);
	mat_set(mat_rot, 2, 2, cos(ang));
	mat_set(mat_rot, 2, 3, -sin(ang));
	mat_set(mat_rot, 3, 2, sin(ang));
	mat_set(mat_rot, 3, 3, cos(ang));
	return (mat_rot);
}

static t_mat		*mat_rot_y(float ang)
{
	t_mat			*mat_rot;

	mat_rot = mat_new(4, 4);
	mat_zero(mat_rot);
	mat_set(mat_rot, 2, 2, 1.0f);
	mat_set(mat_rot, 4, 4, 1.0f);
	mat_set(mat_rot, 1, 1, cos(ang));
	mat_set(mat_rot, 1, 3, sin(ang));
	mat_set(mat_rot, 3, 1, -sin(ang));
	mat_set(mat_rot, 3, 3, cos(ang));
	return (mat_rot);
}

static t_mat		*mat_rot_z(float ang)
{
	t_mat			*mat_rot;

	mat_rot = mat_new(4, 4);
	mat_zero(mat_rot);
	mat_set(mat_rot, 3, 3, 1.0f);
	mat_set(mat_rot, 4, 4, 1.0f);
	mat_set(mat_rot, 1, 1, cos(ang));
	mat_set(mat_rot, 1, 2, -sin(ang));
	mat_set(mat_rot, 2, 1, sin(ang));
	mat_set(mat_rot, 2, 2, cos(ang));
	return (mat_rot);
}

t_mat				*gen_rot_mat(t_obj **o)
{
	t_mat			*mat_rot;

	if ((*o)->rot_angle > -360.0f && (*o)->rot_angle < 360.0f)
		(*o)->rot_angle += (*o)->rot_clockwise * 0.01f;
	else
		(*o)->rot_angle = 0.0f;
	if ((*o)->rot_type == 'y')
		mat_rot = mat_rot_y((*o)->rot_angle);
	else if ((*o)->rot_type == 'x')
		mat_rot = mat_rot_x((*o)->rot_angle);
	else
		mat_rot = mat_rot_z((*o)->rot_angle);
	return mat_rot;
}
