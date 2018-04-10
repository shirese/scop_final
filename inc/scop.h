/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 14:16:30 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/31 19:22:09 by chaueur          ###   ########.fr       */
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
# define MAX_LINE		256
# define MAX_CHAR		80
# define W_W			1440
# define W_H			1080
# define VERTEX_SHADER	"shaders/vertex_shader.vert"
# define FRAG_SHADER	"shaders/frag_shader.frag"
# define TEXTURE_FILE	"resources/cat.tga"

typedef struct		s_vec
{
	float			x;
	float			y;
	float			z;
}					t_vec;

typedef struct		s_mat
{
	float			*array;
	int				width;
	int				height;
}					t_mat;

typedef struct		s_tga
{
	char			type;
	unsigned int	height;
	unsigned int	width;
	char			bit_count;
	char			chan_depth;
	unsigned char	*data;
}					t_tga;

typedef struct		s_mtl
{
	t_vec			*ka;
	t_vec			*kd;
	t_vec			*ks;
	float			d;
	size_t			illum;
	float			ni;
	float			ns;
}					t_mtl;

typedef struct		s_light
{
	GLuint			light;
	GLuint			diff;
	GLuint			ambiant;
	GLuint			spec;
}					t_light;

typedef struct		s_obj
{
	char			*folder;
	char			*name;
	char			*lighting;
	char			*mtllib;
	char			*mtl_name;
	t_mtl			*mtl;
	t_vec			*center;
	t_vec			*trans;

	float			*p;
	int				p_size;

	t_vec			**v;
	t_vec			**vn;
	t_vec			**vt;
	size_t			v_size;
	size_t			vn_size;

	int				*v_index;
	int				*vn_index;
	int				*vt_index;
	size_t			v_index_size;
	size_t			vn_index_size;
	size_t			vt_index_size;

	int				**f;
	size_t			f_size;
	t_vec			**f_n;

	size_t			rot;
	int				rot_clockwise;
	float			rot_angle;
	char			rot_type;
	GLuint			shader;

	GLuint			uv;
	float			*uv_data;
	double			*k;

	GLuint			vao;
	GLuint			vbo;
	GLuint			vco;
	GLuint			vnbo;
	GLuint			tex;
	GLuint			tex_id;
	t_light			*light_env;
}					t_obj;

typedef struct		s_env
{
	GLFWwindow		*win;
	t_obj			*obj;
}					t_env;

void				compute_f_v(int *f, size_t *i, t_vec **v, float *ret);
void				compute_normals(t_obj **o);
void				fade_out(t_obj *o);
void				gen_grayscale(float **f, size_t i);
void				gen_light(t_obj *o);
void				get_face(t_obj **obj);
void				gen_rot(t_obj **o);
void				gen_scale(t_obj *o);
void				init_obj(t_obj **obj);
void				init_rendering(t_obj **obj);
void				init_light_env(t_light **l, GLuint *shader);
void				init_uv(t_obj **o);
void				init_vao(t_obj **o);
void				init_vbo(t_obj **o);
void				init_vco(t_obj **o);
void				init_vnbo(t_obj **o);
void				print_obj(t_obj obj);
void				push(char type, void *val, size_t i, void **f);
void				push_vec(t_vec v, size_t size, t_vec ***v_arr);
void				render_obj(t_env *e);
void				init_obj_infos(char *f, t_obj **o);
GLuint				load_shaders(const char *v_file, const char *frag_file);
int					parse_obj(char *file, t_obj **o);
int					parse_mtl_obj(t_obj **o);
t_mat				*gen_trans_origin_mat(int inv, t_obj *obj);
t_mat				*gen_rot_mat(t_obj **obj);
t_mat				*gen_mvp(void);
void				gen_uniform_mat_4(char *name, t_mat *mat, GLuint shader);
t_mat				*mat_identity(void);
t_mat				*mat_mult(t_mat *m1, t_mat *m2);
t_mat				*mat_new(int width, int height);
t_mat				*mat_persp(float ang, float rat, float near, float far);
void				mat_trans(t_vec v, t_mat **m);
t_mat				*mat_view(t_vec *eye, t_vec *center, t_vec *u);
void				print_mat(t_mat *m);
void				mat_set(t_mat *m, int x, int y, float val);
void				mat_set_col(t_mat *m, int y, int ac, ...);
void				mat_set_row(t_mat *m, int x, int ac, ...);
void				mat_zero(t_mat *dest);
float				*mat_to_float(t_mat *m);

t_vec				*vec_cross_prod(t_vec *v1, t_vec *v2);
t_vec				*vec_offset(t_vec *v1, t_vec *v2);
t_vec				*vec_new(float x, float y, float z);
float				vec_dot_prod(t_vec *v1, t_vec *v2);
void				vec_normalize(t_vec *v);
void				vec_rev(t_vec *v);

void				activate_texture(t_obj **o);
void				find_texture_space(t_obj **o);
void				gen_uv(t_obj **o);
void				load_texture(char *file, t_obj **o);

void				key_callback(GLFWwindow *w, int k, int s, int a, int m);
void				find_center(t_obj **o);
void				rescale_v(t_obj **o);
t_vec				gen_trans(t_obj *o);

void				gen_fade(t_obj *o);

#endif
