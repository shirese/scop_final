/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 17:18:11 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/31 19:27:14 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void			transf_obj(t_obj **o)
{
	static t_mat	*mat_rot;
	t_mat			*mat_mvp;

	mat_mvp = gen_mvp();
	mat_trans(gen_trans(*o), &mat_mvp);
	if ((*o)->rot)
		mat_rot = gen_rot_mat(o);
	if (mat_rot)
	{
		mat_trans(*(*o)->center, &mat_rot);
		mat_mvp = mat_mult(mat_mvp, mat_rot);
		vec_rev((*o)->center);
		mat_trans(*(*o)->center, &mat_rot);
		vec_rev((*o)->center);
	}
	else
		mat_trans(*(*o)->center, &mat_mvp);
	gen_uniform_mat_4("mat_mvp", mat_mvp, (*o)->shader);
}

static void			gen_v_arr(t_obj *o)
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindVertexArray(o->vao);
}

void				render_obj(t_env *e)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gen_v_arr(e->obj);
	gen_rot(&e->obj);
	gen_scale(e->obj);
	transf_obj(&e->obj);
	gen_fade(e->obj);
	glUseProgram(e->obj->shader);
	glDrawArrays(GL_TRIANGLES, 0, e->obj->p_size);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glfwSwapBuffers(e->win);
	glfwPollEvents();
}

void				init_rendering(t_obj **o)
{
	glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDisable(GL_CULL_FACE);
	init_obj(o);
	glUseProgram((*o)->shader);
	init_vbo(o);
	init_vco(o);
	init_uv(o);
}
