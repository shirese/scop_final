/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice_projection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 14:19:10 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/25 14:53:00 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void			gen_uniform_mat_4(char *name, t_mat *mat, GLuint shader)
{
	float			*f_mat;
	GLuint			m_id;

	f_mat = mat_to_float(mat);
	m_id = glGetUniformLocation(shader, name);
	glUniformMatrix4fv(m_id, 1, GL_FALSE, &f_mat[0]);
}

t_mat				*mat_persp(float ang, float rat, float near, float far)
{
	t_mat			*mat;
	float			tan_half_ang;

	mat = mat_new(4, 4);
	mat_zero(mat);
	ang *= 0.01745329252f;
	tan_half_ang = tan(ang / 2.0f);
	mat_set(mat, 1, 1, 1.0f / (rat * tan_half_ang));
	mat_set(mat, 2, 2, 1.0f / (tan_half_ang));
	mat_set(mat, 3, 3, -(far + near) / (far - near));
	mat_set(mat, 3, 4, -1.0f);
	mat_set(mat, 4, 3, -(2.0f * far * near) / (far - near));
	return (mat);
}

t_mat				*mat_view(t_vec *eye, t_vec *center, t_vec *u)
{
	t_mat			*m;
	t_vec			*forward;
	t_vec			*side;
	t_vec			*up;

	m = mat_new(4, 4);
	forward = malloc(sizeof(t_vec));
	forward->x = center->x - eye->x;
	forward->y = center->y - eye->y;
	forward->z = center->z - eye->z;
	vec_normalize(forward);
	side = vec_cross_prod(forward, u);
	vec_normalize(side);
	up = vec_cross_prod(side, forward);
	mat_zero(m);
	mat_set_row(m, 1, 3, side->x, side->y, side->z);
	mat_set_row(m, 2, 3, up->x, up->y, up->z);
	mat_set_row(m, 3, 3, -forward->x, -forward->y, -forward->z);
	mat_set_col(m, 4, 3, -vec_dot_prod(side, eye), -vec_dot_prod(up, eye), vec_dot_prod(forward, eye));
	mat_set(m, 4, 4, 1.0f);
	free(center);
	free(eye);
	free(up);
	free(forward);
	return m;
}

t_mat				*gen_mvp(t_obj **o)
{
	t_mat			*mvp;
	t_mat			*p;
	t_mat			*tmp;
	t_mat			*v;
	t_mat			*i;

	i = mat_identity();
	p = mat_persp(45.0f, 16.0f / 9.0f, 0.1f, 100.0f);
	v = mat_view(vec_new(4.0f, 3.0f, -3.0f), vec_new(0.0f, 0.0f, 0.0f), vec_new(0.0f, 1.0f, 0.0f));
	gen_uniform_mat_4("mat_m", i, (*o)->shader);
	gen_uniform_mat_4("mat_v", v, (*o)->shader);
	tmp = mat_mult(p, v);
	mvp = mat_mult(tmp, i);
	free(p->array);
	free(p);
	free(tmp->array);
	free(tmp);
	free(v->array);
	free(v);
	free(i->array);
	free(i);
	return (mvp);
}
