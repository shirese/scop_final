/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 17:18:11 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/27 18:04:35 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static t_vec		find_center(t_obj **o)
{
	size_t			i;
	double			min_xyz[3];
	double			max_xyz[3];
	t_vec			center;

	i = (*o)->v_size - 1;
	min_xyz[0] = (*o)->v[i]->x;
	min_xyz[1] = (*o)->v[i]->y;
	min_xyz[2] = (*o)->v[i]->z;
	memcpy(max_xyz, min_xyz, sizeof(min_xyz));
	while (i--)
	{
		min_xyz[0] = fmin(min_xyz[0], (*o)->v[i]->x);
		max_xyz[0] = fmax(max_xyz[0], (*o)->v[i]->x);
		min_xyz[1] = fmin(min_xyz[1], (*o)->v[i]->y);
		max_xyz[1] = fmax(max_xyz[1], (*o)->v[i]->y);
		min_xyz[2] = fmin(min_xyz[2], (*o)->v[i]->z);
		max_xyz[2] = fmax(max_xyz[2], (*o)->v[i]->z);
	}
	center.x = (float)((min_xyz[0] + max_xyz[0]) / 2);
	center.y = (float)((min_xyz[1] + max_xyz[1]) / 2);
	center.z = (float)((min_xyz[2] + max_xyz[2]) / 2);
	return (center);
}

static void			trans_to_center(int sense, t_obj **o, t_mat **m)
{
	t_vec			center;

	center = find_center(o);
	if (sense == 1)
		mat_trans(center, m);
	else
	{
		vec_rev(&center);
		mat_trans(center, m);
	}
}

static void			transf_obj(t_obj **o)
{
	static t_mat	*mat_rot;
	t_mat			*mat_tmp;
	t_mat			*mat_mvp;

	// compute_normals(o);
	t_vec v;
	v.x = 1.0f;
	v.y = 1.0f;
	v.z = 0.0f;
	mat_mvp = gen_mvp(o);
	mat_trans(v, &mat_mvp);
	if ((*o)->rot)
		mat_rot = gen_rot_mat(o);
	if (mat_rot)
	{
		trans_to_center(1, o, &mat_mvp);
		mat_tmp = mat_mvp;
		mat_mvp = mat_mult(mat_tmp, mat_rot);
		trans_to_center(0, o, &mat_mvp);
		free(mat_tmp->array);
		free(mat_tmp);
	}
	gen_uniform_mat_4("mat_mvp", mat_mvp, (*o)->shader);
}

void				render_obj(t_env *e)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnableVertexAttribArray (0);
	glEnableVertexAttribArray (1);
	glBindVertexArray(e->obj->vao);
	glUseProgram(e->obj->shader);
	gen_rot(&e->obj);
	// Generate MVP + ROT
	transf_obj(&e->obj);
	// gen_light(e->obj);
	glDrawArrays (GL_TRIANGLES, 0, e->obj->p_count);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	// Swap buffers
	glfwSwapBuffers(e->win);
	glfwPollEvents();
}

void				gen_light(t_obj *o)
{
	t_vec			*light;
	t_vec			*d;

	light = vec_new(4.0f, 4.0f, 4.0f);
	d = vec_new(4.0f, 4.0f, 4.0f);
	glUniform3f(o->light_env->light, light->x, light->y, light->z);
	if (o->mtl)
	{
		glUniform3f(o->light_env->diff, o->mtl->kd->x, o->mtl->kd->y, o->mtl->kd->z);
		glUniform3f(o->light_env->spec, o->mtl->ks->x, o->mtl->ks->y, o->mtl->ks->z);
		glUniform3f(o->light_env->ambiant, o->mtl->ka->x, o->mtl->ka->y, o->mtl->ka->z);
	}
	else
	{
		// glUniform3f(o->light_env->light, light->x, light->y, light->z);
		glUniform3f(o->light_env->diff, 1, 1, 0);
		glUniform3f(o->light_env->spec, 0.3, 0.3, 0.3);
		glUniform3f(o->light_env->ambiant, 0.3, 0.3, 0.3);
	}
	free(light);
}

void				init_rendering(t_obj **o)
{
	glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	// glEnable(GL_CULL_FACE);
	glDisable(GL_CULL_FACE);
	// Init obj (set render var, load shaders)
	init_obj(o);
	// Load it into VBO
	init_vbo(o);
	// init_vco(o);
	// init_vnbo(o);
	glUseProgram((*o)->shader);
	// init_light_env(&(*o)->light_env, &(*o)->shader);
	// (*o)->light_env->light = glGetUniformLocation((*o)->shader, "light");
}
