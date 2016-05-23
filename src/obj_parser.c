/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 10:16:09 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/23 17:29:34 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int			parse_triangle_v(char *l, int *v, t_obj **o)
{
	static int		c;

	if (sscanf(l, "%d%*c%n", &v[0], &c) == 1)
		push('i', &v[0], ++(*o)->v_index_size, (void **)&((*o)->v_index));
	else if (sscanf(l, "%d/%d%*c%n", &v[0], &v[1], &c) == 2)
	{
		push('i', &v[0], ++(*o)->v_index_size, (void **)&(*o)->v_index);
		push('i', &v[1], ++(*o)->vt_index_size, (void **)&(*o)->vt_index);
	}
	else if (sscanf(l, "%d/%d/%d%*c%n", &v[0], &v[1], &v[2], &c) == 3)
	{
		push('i', &v[0], ++(*o)->v_index_size, (void **)&(*o)->v_index);
		push('i', &v[1], ++(*o)->vt_index_size, (void **)&(*o)->vt_index);
		push('i', &v[2], ++(*o)->vn_index_size, (void **)&(*o)->vn_index);
	}
	else if (sscanf(l, "%d//%d%*c%n", &v[0], &v[1], &c) == 2)
	{
		push('i', &v[0], ++(*o)->v_index_size, (void **)&(*o)->v_index);
		push('i', &v[1], ++(*o)->vn_index_size, (void **)&(*o)->vn_index);
	}
	return c;
}

static int			parse_face(char *l, t_obj **o)
{
	int				tmp[4];
	int				i;
	int				ret;

	l += 2;
	ret = 0;
	i = 0;
	while (*l)
	{
		if (i > 3)
			return (-1);
		else
			ret = parse_triangle_v(l, tmp, o);
		l += ret;
		i++;
	}
	return (1);
}

static int			parse_v(char *l, t_obj **o)
{
	float			tmp[3];
	t_vec			***v;
	t_vec			v_ret;

	if (sscanf(l, "%*s %f %f %f", &tmp[0], &tmp[1], &tmp[2]) == 3)
	{
		if (strncmp(l, "v ", 2) == 0)
			v = &((*o)->v);
		else if (strncmp(l, "vn", 2) == 0)
			v = &((*o)->vn);
		else if (strncmp(l, "vt", 2) == 0)
			v = &((*o)->vt);
		else
			return (-1);
		v_ret.x = tmp[0];
		v_ret.y = tmp[1];
		v_ret.z = tmp[2];
		push_vec(v_ret, ++(*o)->v_size, v);
		return (1);
	}
	return (-1);
}

static void			init_obj_infos(t_obj **o)
{
	(*o) = malloc(sizeof(t_obj));
	(*o)->name = malloc(sizeof(char) * 256);
	(*o)->lighting = malloc(sizeof(char) * 256);
	(*o)->mtllib = malloc(sizeof(char) * 256);
	(*o)->mtl = malloc(sizeof(char) * 256);
	(*o)->v = NULL;
	(*o)->v_size = 0;
	(*o)->v_index = NULL;
	(*o)->v_index_size = 0;
	(*o)->vn = NULL;
	(*o)->vn_index = NULL;
	(*o)->vn_index_size = 0;
	(*o)->vt = NULL;
	(*o)->vt_index = NULL;
	(*o)->vt_index_size = 0;
	(*o)->f = NULL;
	(*o)->f_size = 0;
	(*o)->shader = 0;
}

int					parse_obj(char *file, t_obj **o)
{
	char			line[256];
	static int		ret;
	FILE			*f;

	if ((f = fopen(file, "r")))
	{
		ret = 1;
		init_obj_infos(o);
		while (fgets(line, sizeof(line), f))
		{
			if (line[0] == 'o')
				ret *= sscanf(line + 2, "%s", (*o)->name);
			else if (line[0] == 'm')
				ret *= sscanf(line, "%*s %s", (*o)->mtllib);
			else if (line[0] == 's')
				ret *= sscanf(line + 2, "%s", (*o)->lighting);
			else if (line[0] == 'v')
				ret *= parse_v(line, o);
			else if (line[0] == 'u')
				ret *= sscanf(line + 2, "%s", (*o)->mtl);
			else if (line[0] == 'f')
				ret = parse_face(line, o);
		}
		get_face(o);
		print_obj(**o);
	}
	return (ret);
}
