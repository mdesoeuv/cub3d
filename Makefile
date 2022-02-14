# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/18 11:13:54 by vchevill          #+#    #+#              #
#    Updated: 2022/02/14 14:00:23 by vchevill         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = gcc -Wall -Werror -Wextra

SRCS =	main.c \
		ft_check_file_extension.c \
		ft_check_map.c \
		ft_create_map.c \
		ft_init_vars.c \
		ft_print_error.c \
		ft_get_textures_path.c \
		get_next_line.c

GNL_OBJS = ${addprefix ${GNL_DIR}, ${GNL:.c=.o}}

SRCS_FILES = $(addprefix srcs/, $(SRCS))

OBJS = $(SRCS:.c=.o)

OBJS_FILES = $(addprefix objs/, $(OBJS))

LIB = libft/libft.a

GNL = libft/libft.a

all : libft minilibx $(NAME)

$(NAME)	:	$(OBJS_FILES) $(LIB) Makefile
			$(CC) $(OBJS_FILES) -Lminilibx -lmlx -framework OpenGL -framework AppKit -o $(NAME) libft/libft.a minilibx/libmlx.a

libft	:	
			$(MAKE) -C libft

minilibx	:	
			$(MAKE) -C minilibx 

objs/%.o:	srcs/%.c	 includes/get_next_line.h includes/cub3d.h libft/libft.h minilibx/mlx.h minilibx/mlx_int.h minilibx/mlx_new_window.h minilibx/mlx_opengl.h minilibx/mlx_png.h
			@mkdir -p objs
			$(CC) -c $< -o $@ 
			
clean	:
			rm -rf objs/
			make clean -C libft
			make clean -C minilibx

fclean	:	clean
			rm -f $(NAME)
			make fclean -C libft

re		:	fclean all

.PHONY	:	libft all clean re fclean minilibx
