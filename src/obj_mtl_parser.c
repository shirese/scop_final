/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_mtl_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 15:14:41 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/26 12:45:28 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int			parse_r_g_b(char *l, t_obj **o)
{
	t_vec			*v;

	v = malloc(sizeof(t_vec));
	if (sscanf(l, "%*s %f %f %f", &v->x, &v->y, &v->z) != 3)
		return (-1);
	if (l[1] == 'a')
		(*o)->mtl->ka = v;
	else if (l[1] == 'd')
		(*o)->mtl->kd = v;
	else if (l[1] == 's')
		(*o)->mtl->ks = v;
	return (1);
}
static int			parse_mat_line(char *l, t_obj **o)
{
	char			tmp[256];
	static int		ret = 1;

	if (l[0] == 'n' && sscanf(l, "%*s %s", tmp))
	{
		if (strcmp(tmp, (*o)->mtl_name) != 0)
		{
			printf("Only one material supported\n");
			return -1;
		}
	}
	else if (l[0] == 'N')
	{
		if (l[1] == 'i')
			ret = sscanf(l, "%*s %f", &(*o)->mtl->ni);
		else if (l[1] == 's')
			ret = sscanf(l, "%*s %f", &(*o)->mtl->ns);
	}
	else if (l[0] == 'K')
		ret = (parse_r_g_b(l, o));
	else if (l[0] == 'i')
		ret = sscanf(l, "%*s %zu", &(*o)->mtl->illum);
	else if (l[0] == 'd')
		ret = sscanf(l, "%*s %f", &(*o)->mtl->d);
	return (ret);
}
int					parse_mtl_obj(t_obj **o)
{
	static int		ret = -1;
	char			*file;
	char			line[256];
	FILE			*f;

	file = malloc(sizeof(char) * (strlen((*o)->folder) + strlen((*o)->mtllib) + 1));
	strcpy(file, (*o)->folder);
	strcat(file, (*o)->mtllib);
	if ((f = fopen(file, "r")))
	{
		(*o)->mtl = malloc(sizeof(t_mtl));
		if (!(*o)->mtl)
			return (ret);
		while (fgets(line, sizeof(line), f))
		{
			if (parse_mat_line(line, o) == -1)
				return (ret);
		}
		free(file);
		ret = 1;
	}
	return (ret);
}
