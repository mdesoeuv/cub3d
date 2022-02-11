# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/18 11:13:54 by vchevill          #+#    #+#              #
#    Updated: 2022/02/11 10:58:01 by vchevill         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = gcc -Wall -Werror -Wextra

SRCS =	main.c \
		ft_check_file_extension.c \
		ft_check_map.c \
		ft_create_map.c \
		ft_init_map.c \
		ft_print_error.c \
		ft_init_window_images.c \
		handlers.c \
		render.c \
		ft_moves.c \
		get_next_line.c \
		get_next_line_utils.c

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

objs/%.o:	srcs/%.c	 includes/get_next_line.h includes/so_long.h libft/libft.h minilibx/mlx.h
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
