# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/02 10:55:23 by chaueur           #+#    #+#              #
#    Updated: 2016/05/29 17:31:44 by chaueur          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= scop
TEST			= test
CC				= gcc
FLAG			= -c -Wall -Werror -Wextra -pedantic
INCS			= -I inc/

SRC				= scop.c obj_init.c obj_parser.c obj_mtl_parser.c obj_render.c \
					obj_texture.c load_shaders.c glfw.c compute_vertices.c
SRC_UTILS		= matrice.c matrice_projection.c matrice_utils.c\
				rotate.c utils.c vector.c
SRCS			= $(addprefix $(DIR_SRC)/, $(SRC))
SRCS_UTILS		= $(addprefix $(DIR_SRC_UTILS)/, $(SRC_UTILS))

LIB 			= -framework OpenGl -framework Cocoa -framework OpenGL \
				-framework IOKit -framework CoreFoundation -framework CoreVideo \
				glfw-3.1.2/src/libglfw3.a
DIR_SRC			= src
DIR_SRC_UTILS	= src/utils
DIR_INC			= inc
DIR_LIST		= src
DIR_OBJ			= obj
OBJ				= $(addprefix $(DIR_OBJ)/, $(SRC:.c=.o))
OBJ_UTILS		= $(addprefix $(DIR_OBJ)/, $(SRC_UTILS:.c=.o))

all : $(NAME)

debug :
	gcc -g -c $(SRCS) $(SRCS_UTILS) $(INCS)
	@/bin/mkdir $(DIR_OBJ); \
	mv $(SRC:.c=.o) $(SRC_UTILS:.c=.o) $(DIR_OBJ)/
	gcc -o $(NAME) $(OBJ) $(OBJ_UTILS) $(LIB)
	@printf "\e[32m------------------------------------------------------\e[0m\n"
	@printf '\e[34m%-51s\e[0m\e[32m[✔]\e[0m\n' "created debug"
	@printf "\e[32m------------------------------------------------------\e[0m\n"

$(NAME) :
	gcc $(FLAG) $(SRCS) $(SRCS_UTILS) $(INCS)
	@/bin/mkdir $(DIR_OBJ); \
	mv $(SRC:.c=.o) $(SRC_UTILS:.c=.o) $(DIR_OBJ)/
	gcc -o $(NAME) $(OBJ) $(OBJ_UTILS) $(LIB)
	@printf "\e[32m------------------------------------------------------\e[0m\n"
	@printf '\e[34m%-51s\e[0m\e[32m[✔]\e[0m\n' "created scop"
	@printf "\e[32m------------------------------------------------------\e[0m\n"


$(addprefix $(DIR_OBJ)/, %.o) : %.c
	@printf "compiling \e[33m%-41s\e[0m" "$@"
	@$(CC) $(FLAG) $@ $<
	@printf "\e[32m[✔]\e[0m\n"

clean :
	@if [ -e '$(DIR_OBJ)' ]; then \
		/bin/rm	-rf $(DIR_OBJ); \
		printf "\e[32m[✔]\e[0m project %s cleaned.\n" $(NAME); \
		fi

fclean : clean
	@if [ -e '$(NAME)' ]; then \
		/bin/rm -f $(NAME); \
		printf "\e[32m[✔]\e[0m project %s fcleaned.\n" $(NAME); \
		fi

re : fclean all

.PHONY:	clean fclean re
