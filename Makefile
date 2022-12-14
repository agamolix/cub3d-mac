# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atrilles <atrilles@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 17:07:37 by atrilles          #+#    #+#              #
#    Updated: 2022/12/05 16:15:52 by atrilles         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######## PROJECT ###############################################################

NAME = cub3D

######## DIRECTORIES ###########################################################

#SRC_DIR	= src/

######## SOURCE FILES ##########################################################

SRC_FILES =		main gnl_utils   file   utils_global  init  exit   atoi color utils_file distance text_color keys parse populate rays texture_parse rgb_errors
# SRC_FILES =		main  gnl		gnl_utils   file   utils_global  init  exit   atoi color utils_file distance text_color keys parse populate rays

#SRC = $(addsuffix .c, $(SRC_FILES))
#OBJ = $(addsuffix .o, $(SRC_FILES))
OBJ = $(addsuffix .o, $(SRC_FILES))
LIBFTDIR = ./libftextended
LIBFTHEADERS = $(LIBFTDIR)/headers
INC_LFT = $(LIBFTDIR)/libft.a -I $(LIBFTHEADERS)

######## FLAGS #################################################################

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = 


######## RULES #################################################################

all: $(NAME)
$(LIBFTDIR)/libft.a:
	# git submodule add --name libft https://github.com/ErwannMillon/libftextended.git ./libftextended
	git submodule update --recursive --init
	make -C $(LIBFTDIR)

$(NAME): $(LIBFTDIR)/libft.a $(OBJ)
#	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	$(CC) -g $(CFLAGS) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(INC_LFT)

asan: $(OBJ) 
#	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
		$(CC) -fsanitize=address $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o \
			$(NAME) $(INC_LFT)

# linux	$(CC) $(OBJ) -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c
# linux	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx -O3 -c $< -o $@
	$(CC)  -I ./mlx/minilibx_opengl_20191021/ -Imlx -c $< -o $@ -I $(LIBFTHEADERS) 
	
.PHONY: clean fclean re test

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all
