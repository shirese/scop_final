/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice_transf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 11:08:17 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/24 16:16:22 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_mat				*mat_trans(t_vec *e)
{
	t_mat			*m;
	int				i;

	i = 1;
	m = mat_identity();
	while (i <= 3)
	{
		if (i == 1)
			mat_set(m, 4, i, e->x);
		else if (i == 2)
			mat_set(m, 4, i, e->y);
		else
			mat_set(m, 4, i, e->z);
		i++;
	}
	return (m);
}

int					gen_rot_mat_y(GLuint *shader, t_obj *obj)
{
	t_mat			*mat_rot;
	float			*f_rot;
	GLuint			m_id;

	mat_rot = mat_new(4, 4);
	mat_zero(mat_rot);
	mat_set(mat_rot, 2, 2, 1.0f);
	mat_set(mat_rot, 4, 4, 1.0f);
	mat_set(mat_rot, 1, 1, cos(obj->rot));
	mat_set(mat_rot, 1, 2, sin(obj->rot));
	mat_set(mat_rot, 3, 1, -sin(obj->rot));
	mat_set(mat_rot, 3, 2, cos(obj->rot));
	f_rot = mat_to_float(mat_rot);
	m_id = glGetUniformLocation(*shader, "mat_rot");
	glUniformMatrix4fv(m_id, 1, GL_FALSE, &f_rot[0]);
	obj->rot += 0.1f;
	free(mat_rot->array);
	free(mat_rot);
	free(f_rot);
	return 0;
}
