/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_shaders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 11:15:30 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/26 14:55:12 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void			load_shader(const char *shader_file, GLuint *shader_id)
{
	FILE		*f;
	char		line[256];
	char		*shader;
	const char	*test;
	int			size;

	shader = malloc(sizeof(char) * 4096);
	size = 0;
	if ((f=fopen(shader_file, "r")))
	{
		while (fgets(line, 256, f))
		{
			size += strlen(line);
			strncat(shader, line, strlen(line));
		}
		test = shader;
		printf("\nCompiling shader: %s\n", shader_file);
		glShaderSource(*shader_id, 1, &test, NULL);
		glCompileShader(*shader_id);
		free(shader);
		fclose(f);
	}
}

GLuint			load_shaders(const char *vertex_file, const char *fragment_file)
{
	GLuint		shader;
	GLuint		vs;
	GLuint		fs;

	vs = glCreateShader(GL_VERTEX_SHADER);
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	load_shader(vertex_file, &vs);
	load_shader(fragment_file, &fs);
	shader = glCreateProgram();
	glAttachShader (shader, fs);
	glAttachShader (shader, vs);
	glLinkProgram (shader);
	glDetachShader(shader, fs);
	glDetachShader(shader, vs);
	return shader;
}
