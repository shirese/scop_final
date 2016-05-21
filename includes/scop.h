#ifndef SCOP_H
#define SCOP_H

#include <fcntl.h>
#include <mlx.h>
#include <mlx_opengl.h>
#include <libc.h>
#include <math.h>
#include <OpenGL/gl3.h>
#include "libft.h"

// One triangle == 9 points
#define TRIANGLE 9

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

typedef struct		s_obj
{
	char			*name;
	char			**group;
	char			**mtllib;
	static int		smooth_shading;
	t_vec			*face_normals;
	t_vec			*vertex_normal;
	GLuint			shader;

	float			**v;
	int				v_count;

	float			rot;
	int				triangles;

	float			*p;
	int				p_count;

	float			*uv;
	int				uv_count;

	float			*n;
	int				n_count;

	int				face_index;
	int				v_index;
}					t_obj;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	t_obj		*obj;
}				t_env;

t_vec		*vec_cross_prod(t_vec *v1, t_vec *v2);
t_vec		*vec_new(float x, float y, float z);
float		vec_dot_prod(t_vec *v1, t_vec *v2);
void		vec_normalize(t_vec *v);
void		vec_rev(t_vec *v);

t_mat		*mat_identity(void);
t_mat		*mat_perspective(float angle, float ratio, float near, float far);
t_mat		*mat_mult(t_mat *m1, t_mat *m2);
t_mat		*mat_new(int width, int height);
t_mat		*mat_view(t_vec *center, t_vec *eye, t_vec *up);
void		print_mat(t_mat *m);
void		mat_set(t_mat *m, int x, int y, float val);
void		mat_set_col(t_mat *m, int y, int ac, ...);
void		mat_set_row(t_mat *m, int x, int ac, ...);
void		mat_zero(t_mat *dest);
float		*mat_to_float(t_mat *m);


void		compute_normals(t_obj *obj);
void		compute_vertex(t_obj *obj);
int			get_vertices(t_list *file, t_obj **obj);
int			get_faces(t_list *file, t_obj **obj);
void		add_points(float *points, t_obj **obj);
void		add_face(t_obj **obj);
void		vector_normalize(t_vec *n, t_vec *v3);
int			obj_parse(char *filename, t_obj **obj);
GLuint		load_shaders(const char *vertex_file, const char *fragment_file);

int			loop_hook(t_env *e);
void		print_obj(t_obj *o);

void		push(float **f, int i, float val);

#endif
