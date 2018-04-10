/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_shaders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 11:15:30 by chaueur           #+#    #+#             */
/*   Updated: 2016/05/31 17:07:29 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		check_shader(GLuint shader_id)
{
	GLint		result;
	int			log_len;
	char		*error_log;

	error_log = NULL;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_len);
	if (log_len > 0)
	{
		glGetShaderInfoLog(shader_id, log_len, NULL, &error_log[0]);
		printf("%s\n", &error_log[0]);
	}
}

void			load_shader(const char *shader_file, GLuint *shader_id)
{
	FILE		*f;
	char		line[256];
	char		*shader;
	const char	*test;
	int			size;

	f = NULL;
	shader = malloc(sizeof(char) * 4096);
	bzero(shader, strlen(shader));
	size = 0;
	if (shader && (f = fopen(shader_file, "r")))
	{
		while (fgets(line, sizeof(line), f))
		{
			size += strlen(line);
			strncat(shader, line, strlen(line));
		}
		test = shader;
		check_shader(*shader_id);
		glShaderSource(*shader_id, 1, &test, NULL);
		glCompileShader(*shader_id);
		free(shader);
		if (f)
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
	if (fs && vs)
	{
		glAttachShader(shader, fs);
		glAttachShader(shader, vs);
		glLinkProgram(shader);
		glDetachShader(shader, fs);
		glDetachShader(shader, vs);
		return (shader);
	}
	return (0);
}
