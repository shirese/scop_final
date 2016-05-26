/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 17:18:11 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/26 19:02:01 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void			transf_obj(t_obj **o)
{
	static t_mat	*mat_rot;
	t_mat			*mat_tmp;
	t_mat			*mat_mvp;

	// compute_normals(o);
	mat_mvp = gen_mvp(o);
	if ((*o)->rot)
		mat_rot = gen_rot_mat(o);
	if (mat_rot)
	{
		mat_tmp = mat_mvp;
		mat_mvp = mat_mult(mat_tmp, mat_rot);
		free(mat_tmp);
	}
	gen_uniform_mat_4("mat_mvp", mat_mvp, (*o)->shader);
}

static void			gen_v_arr(t_obj *o)
{
	glBindBuffer(GL_ARRAY_BUFFER, o->vbo);
	glBindVertexArray(o->vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, o->vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, o->vco);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
}

void				render_obj(t_env *e)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(e->obj->shader);
	gen_rot(&e->obj);
	// Generate MVP + ROT
	transf_obj(&e->obj);

	// gen_light(e->obj);

	gen_v_arr(e->obj);

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
	glClearColor(0.15f, 0.15f, 0.15f, 0.15f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	// glEnable(GL_CULL_FACE);
	glDisable(GL_CULL_FACE);
	glGenVertexArrays(1, &(*o)->vao);
	glBindVertexArray((*o)->vao);
	// Init obj (set render var, load shaders)
	init_obj(o);
	// Load it into VBO
	init_vbo(o);
	init_vco(o);
	// init_vnbo(o);
	glUseProgram((*o)->shader);
	// init_light_env(&(*o)->light_env, &(*o)->shader);
	// (*o)->light_env->light = glGetUniformLocation((*o)->shader, "light");
}
