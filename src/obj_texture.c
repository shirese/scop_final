/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 13:44:12 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/30 17:40:42 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void				gen_uv(t_obj **o)
{
	printf("GEN UV\n");
	int				i;
	int				j;
	double			u;
	double			v;

	i = 0;
	j = 0;
	(*o)->uv_data = malloc(sizeof(float) * (*o)->p_size * 2 / 3);
	printf("%f\n", (*o)->k[0]);
	printf("%f\n", (*o)->k[1]);
	while (i < (*o)->p_size)
	{
		u = (*o)->p[i + 2] * (*o)->k[0];
		v = (*o)->p[i + 1] * (*o)->k[1];
		(*o)->uv_data[j++] = (float)u;
		(*o)->uv_data[j++] = (float)v;
		i += 3;
	}
	for (int i = 0; i < j; ++i)
	{
		if (i && i % 2 == 0)
			printf("\n");
		printf("%f ", (*o)->uv_data[i]);
	}
}
static void			gen_texture(t_tga **tga_file, t_obj **o)
{
	printf("GEN TEX\n");
	// Create one OpenGL texture
	glGenTextures(1, &(*o)->tex_id);
	// // "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, (*o)->tex_id);
	free((*tga_file)->data);
	free((*tga_file));
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (*tga_file)->width, (*tga_file)->height, 0, GL_RGB, GL_UNSIGNED_BYTE, (*tga_file)->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
}

static unsigned	char	*read_tga_24b_rle(FILE *f, long img_size, t_tga *tga_file)
{
	long			i;
	unsigned char	*data;

	i = 0;
	data = malloc(sizeof(unsigned char) * img_size);
	while (i < tga_file->width * tga_file->height)
	{
		data[(i * 3) + 2] = (unsigned char)fgetc(f);
		data[(i * 3) + 1] = (unsigned char)fgetc(f);
		data[(i * 3) + 0] = (unsigned char)fgetc(f);
		i++;
	}
	return (data);
	// for (unsigned int i = 0; i < (tga_file->width * tga_file->height) * 3; i+=3)
	// {
	// 	printf("RGB %d %d %d\n", tga_file->data[i], tga_file->data[i + 1], tga_file->data[i + 2]);
	// }
}

static int			load_tga(char *file, t_tga *tga_file, t_obj **o)
{
	FILE			*f;
	unsigned char	header[18];
	int				color_mode;
	long			img_size;

	f = fopen(file, "rb");
	printf("LOADING TGA\n");
	if (!f)
	{
		fclose(f);
		printf("%s could not be opened\n", file);
		return (0);
	}
	fread(&header, sizeof(char), 18, f);
	tga_file->type = (char) header[2];
	tga_file->width = (int) header[12] | (((char) header[13]) << 8);
	tga_file->height = (int) header[14] | (((char) header[15]) << 8);
	tga_file->bit_count = (char) header[16];
	tga_file->chan_depth = (char) header[17];
	color_mode = tga_file->bit_count / 8;
	img_size = tga_file->width * tga_file->height * color_mode;
	tga_file->data = read_tga_24b_rle(f, img_size, tga_file);
	printf("IMG SIZE %ld\n", img_size);
	printf("========== TGA FILE ==========\n");
	printf("TGA TYPE %d\n", tga_file->type);
	printf("TGA W %d\n", tga_file->width);
	printf("TGA H %d\n", tga_file->height);
	printf("TGA BIT COUNT %d\n", tga_file->bit_count);
	printf("TGA CHAN DEPTH %d\n", tga_file->chan_depth);
	gen_texture(&tga_file, o);
	fclose(f);
	return(1);
}

void				load_texture(char *file, t_obj **o)
{
	t_tga			*tga_file;

	printf("LOADING TEXTURE\n");
	find_texture_space(o);
	tga_file = malloc(sizeof(t_tga));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, (*o)->tex);
	glUniform1i((*o)->tex_id, 0);
	if (load_tga(file, tga_file, o))
		(*o)->tex_id = glGetUniformLocation((*o)->shader, "texture_sample");
	else
		printf("Error while parsing texture\n");
}
