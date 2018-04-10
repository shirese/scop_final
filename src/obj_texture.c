/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 13:44:12 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/31 12:54:29 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void					gen_uv(t_obj **o)
{
	int					i;
	int					j;
	double				u;
	double				v;

	i = 0;
	j = 0;
	(*o)->uv_data = malloc(sizeof(float) * (*o)->p_size * 2 / 3);
	while (i < (*o)->p_size)
	{
		u = (*o)->p[i + 2] * (*o)->k[0];
		v = (*o)->p[i + 1] * (*o)->k[1];
		(*o)->uv_data[j++] = (float)u;
		(*o)->uv_data[j++] = (float)v;
		i += 3;
	}
}

static void				gen_texture(t_tga **tga_f, t_obj **o)
{
	glGenTextures(1, &(*o)->tex_id);
	glBindTexture(GL_TEXTURE_2D, (*o)->tex_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (*tga_f)->width,
		(*tga_f)->height, 0, GL_RGB, GL_UNSIGNED_BYTE, (*tga_f)->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	free((*tga_f)->data);
	free((*tga_f));
}

static unsigned	char	*read_tga_24b_rle(FILE *f, long img_size, t_tga *tga_f)
{
	long				i;
	unsigned char		*data;

	i = 0;
	data = malloc(sizeof(unsigned char) * img_size);
	while (i < tga_f->width * tga_f->height)
	{
		data[(i * 3) + 2] = (unsigned char)fgetc(f);
		data[(i * 3) + 1] = (unsigned char)fgetc(f);
		data[(i * 3) + 0] = (unsigned char)fgetc(f);
		i++;
	}
	return (data);
}

static int				load_tga(char *file, t_tga *tga_f, t_obj **o)
{
	FILE				*f;
	unsigned char		header[18];
	int					color_mode;
	long				img_size;

	f = fopen(file, "rb");
	if (!f)
	{
		fclose(f);
		printf("%s could not be opened\n", file);
		return (0);
	}
	fread(&header, sizeof(char), 18, f);
	tga_f->type = (char)header[2];
	tga_f->width = (int)header[12] | (((char)header[13]) << 8);
	tga_f->height = (int)header[14] | (((char)header[15]) << 8);
	tga_f->bit_count = (char)header[16];
	tga_f->chan_depth = (char)header[17];
	color_mode = tga_f->bit_count / 8;
	img_size = tga_f->width * tga_f->height * color_mode;
	tga_f->data = read_tga_24b_rle(f, img_size, tga_f);
	gen_texture(&tga_f, o);
	fclose(f);
	return (1);
}

void					load_texture(char *file, t_obj **o)
{
	t_tga				*tga_f;

	find_texture_space(o);
	tga_f = malloc(sizeof(t_tga));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, (*o)->tex);
	glUniform1i((*o)->tex_id, 0);
	if (load_tga(file, tga_f, o))
		(*o)->tex_id = glGetUniformLocation((*o)->shader, "texture_sample");
	else
		printf("Error while parsing texture\n");
}
