/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 14:16:30 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/23 18:19:19 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# define GLFW_INCLUDE_GLCOREARB
# include "../glfw-3.1.2/include/GLFW/glfw3.h"
# include <libc.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define MAX_LINE	256
# define MAX_CHAR	80
# define W_W		1200
# define W_H		768

typedef struct	s_vec
{
	float		x;
	float		y;
	float		z;
}				t_vec;

typedef struct	s_mat
{
	float		*array;
	int			width;
	int			height;
}				t_mat;

typedef struct	s_obj
{
	char		*name;
	char		*lighting;
	char		*mtllib;
	char		*mtl;

	t_vec		**v;
	t_vec		**vn;
	t_vec		**vt;
	size_t		v_size;

	int			*v_index;
	int			*vn_index;
	int			*vt_index;
	size_t		v_index_size;
	size_t		vn_index_size;
	size_t		vt_index_size;

	float		*f;
	size_t		f_size;
	float		*f_n;

	float		rot;
	char		rot_type;
	GLuint		shader;

	GLuint		vao;
	GLuint		vbo;
}				t_obj;

typedef struct	s_env
{
	GLFWwindow*	win;
	t_obj		*obj;
}				t_env;

// RENDERING

void				compute_normals(t_obj **o);
void				get_face(t_obj **obj);
void				init_obj(t_obj **obj);
void				init_rendering(t_obj **obj);
void				init_vao(t_obj **o);
void				init_vbo(t_obj **o);
void				print_obj(t_obj obj);
void				push(char type, void *val, size_t i, void **f);
void				push_vec(t_vec v, size_t size, t_vec ***v_arr);
void				render_obj(t_env *e);
GLuint				load_shaders(const char *vertex_file, const char *fragment_file);
int					parse_obj(char *file, t_obj **o);
float				centroid(char axis, float *f, size_t size);

t_mat				*gen_trans_origin_mat(int inv, t_obj *obj);
t_mat				*gen_rot_mat(t_obj **obj);
t_mat				*gen_mvp(void);
void				gen_uniform_mat_4(char *name, t_mat *mat, GLuint shader);
t_mat				*mat_identity(void);
t_mat				*mat_mult(t_mat *m1, t_mat *m2);
t_mat				*mat_new(int width, int height);
t_mat				*mat_persp(float ang, float rat, float near, float far);
t_mat				*mat_trans(t_vec *e);
t_mat				*mat_view(t_vec *eye, t_vec *center, t_vec *u);
void				print_mat(t_mat *m);
void				mat_set(t_mat *m, int x, int y, float val);
void				mat_set_col(t_mat *m, int y, int ac, ...);
void				mat_set_row(t_mat *m, int x, int ac, ...);
void				mat_zero(t_mat *dest);
float				*mat_to_float(t_mat *m);

t_vec				*vec_cross_prod(t_vec *v1, t_vec *v2);
t_vec				*vec_new(float x, float y, float z);
float				vec_dot_prod(t_vec *v1, t_vec *v2);
void				vec_normalize(t_vec *v);
void				vec_rev(t_vec *v);

#endif
