# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chaueur  <chaueur @student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/02 10:55:23 by chaueur           #+#    #+#              #
#    Updated: 2016/05/21 12:45:03 by anonymous        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= scop
TEST			= test
CC				= gcc
FLAG			= -c
INCS			= -I includes/

SRC				= scop.c
SRCS			= $(addprefix $(DIR_SRC)/, $(SRC))

LIB 			= libft/libft.a minilibx_opengl/libmlx.a -framework OpenGL -framework AppKit
DIR_SRC			= src
DIR_INC			= inc
DIR_LIST		= src
DIR_OBJ			= obj
OBJ				= $(addprefix $(DIR_OBJ)/, $(SRC:.c=.o))

all : $(NAME)

debug :
	gcc -g $(FLAG) $(SRCS) $(INCS)
	@/bin/mkdir $(DIR_OBJ); \
	mv $(SRC:.c=.o) $(DIR_OBJ)/
	gcc -o $(NAME) $(OBJ) $(LIB)
	@printf "\e[32m------------------------------------------------------\e[0m\n"
	@printf '\e[34m%-51s\e[0m\e[32m[✔]\e[0m\n' "created scop"
	@printf "\e[32m------------------------------------------------------\e[0m\n"

$(NAME) :
	gcc $(FLAG) $(SRCS) $(INCS)
	@/bin/mkdir $(DIR_OBJ); \
	mv $(SRC:.c=.o) $(DIR_OBJ)/
	gcc -o $(NAME) $(OBJ) $(LIB)
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
