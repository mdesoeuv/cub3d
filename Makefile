# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/18 11:13:54 by vchevill          #+#    #+#              #
#    Updated: 2022/03/01 11:04:48 by mdesoeuv         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = gcc -Wall -Werror -Wextra -g3 

OPTI = -Ofast -march=native -ffast-math

DEBUG = -fsanitize=address

SRCS =	main.c \
		ft_check_file_extension.c \
		ft_check_map.c \
		ft_create_map.c \
		ft_init_vars.c \
		ft_print_error.c \
		ft_get_textures_path.c \
		get_next_line.c \
		ft_rotate_map.c \
		ft_define_texture.c \
		raycaster_2d.c \
		raycaster_3d.c \
		ft_init_window_images.c \
		ft_handlers.c \
		ft_moves.c \
		ft_print_texture.c \
		ft_textures_offset.c \
		ft_raycaster_utils.c

GNL_OBJS = ${addprefix ${GNL_DIR}, ${GNL:.c=.o}}

SRCS_FILES = $(addprefix srcs/, $(SRCS))

OBJS = $(SRCS:.c=.o)

OBJS_FILES = $(addprefix objs/, $(OBJS))

LIB = libft/libft.a

GNL = libft/libft.a

all : libft minilibx $(NAME)

$(NAME)	:	$(OBJS_FILES) $(LIB) Makefile
			$(CC) $(DEBUG) $(OBJS_FILES) -Lminilibx -lmlx -framework OpenGL -framework AppKit -o $(NAME) libft/libft.a minilibx/libmlx.a

libft	:	
			make -C libft

minilibx	:	
			make -C minilibx 

objs/%.o:	srcs/%.c	 includes/get_next_line.h includes/cub3d.h libft/libft.h minilibx/mlx.h minilibx/mlx_int.h minilibx/mlx_new_window.h minilibx/mlx_opengl.h minilibx/mlx_png.h
			@mkdir -p objs
			$(CC) $(DEBUG) $(OPTI) -c $< -o $@ 
			
clean	:
			rm -rf objs/
			make clean -C libft
			make clean -C minilibx

fclean	:	clean
			rm -f $(NAME)
			make fclean -C libft

re		:	fclean all
	
.PHONY	:	libft all clean re fclean minilibx
