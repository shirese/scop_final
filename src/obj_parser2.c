/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 12:08:05 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/31 12:55:27 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static char			*get_folder(char *f)
{
	char			*tmp;
	char			*dst;
	size_t			n;

	tmp = strdup(f);
	tmp += strlen(tmp);
	n = 0;
	while (*tmp-- != '/')
		n++;
	dst = malloc(sizeof(char) * (strlen(f) - n + 2));
	bzero(dst, (strlen(f) - n + 2));
	strncpy(dst, f, strlen(f) - n);
	dst[strlen(dst)] = '/';
	return (dst);
}

void				init_obj_infos(char *f, t_obj **o)
{
	(*o)->name = malloc(sizeof(char) * 256);
	(*o)->folder = get_folder(f);
	(*o)->name = malloc(sizeof(char) * 256);
	(*o)->lighting = malloc(sizeof(char) * 256);
	(*o)->mtllib = NULL;
	(*o)->mtl_name = NULL;
	(*o)->mtl = NULL;
	(*o)->v = NULL;
	(*o)->p_size = 0;
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
