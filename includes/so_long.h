/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 09:54:12 by vchevill          #+#    #+#             */
/*   Updated: 2022/01/20 14:37:06 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "../libft/libft.h"
# include "../minilibx/mlx.h"

# define PLAYER "assets/player.xpm"
# define EXIT "assets/chest_unlocked.xpm"
# define LOCKED "assets/chest_locked.xpm"
# define WALL "assets/wall.xpm"
# define GROUND "assets/ground.xpm"
# define COIN1 "assets/coin/coin1.xpm"
# define W_RAND "assets/walls/wall_random.xpm"

# define ERROR_FILE_EXTENSION_NAME "File given argument does not have \
	 the .ber extension.\n"
# define ERROR_FILE_OPENING "Can't open file given in argument.\n"
# define ERROR_MALLOC "Malloc error. Please free memory space and retry.\n"
# define ERROR_OTHER_CHARS "At least one character in the map is invalid.\
		 (Not 0, 1, C, E or P)\n"
# define ERROR_MISSING_CHARS "One of the characters \"0, 1, P, C, E\" \
		 is missing in the map.\n"
# define ERROR_TOO_MANY_PLAYERS "Too many players in the map.\n"
# define ERROR_NOT_A_RECTANGLE "The map is not a rectangle.\n"
# define ERROR_MINILIBX "Minilibix usage error.\n"
# define ERROR_EDGES "The edges of the map are invalid (must be walls -1-).\n"
# define ERROR_FILENAME_MISSING "Please pass one filename in parameter.\n"

# define IMG_SIZE 48

typedef struct s_img
{
	void	*mlx_img;
	int		width;
	int		height;
	void	*wall;
	void	*exit_l;
	void	*ground;
	void	*player;
	int		line_length;
	void	*coin1;

}	t_img;

typedef struct s_map
{
	int		fd;
	int		line_count;
	size_t	line_len;
	int		count_p;
	int		count_e;
	int		count_c;
	char	*path;
	char	**map;
	int		can_exit;
	int		collected;

}				t_map;

typedef struct s_so_long
{
	void	*mlx;
	void	*win;
	int		steps_count;
	int		player_x;
	int		player_y;
	int		x;
	int		y;
	int		win_height;
	int		win_width;
	t_map	map;
	t_img	img;

}				t_so_long;

void	ft_check_file_extension(char *path, t_so_long *so_long);
void	ft_print_error(char *str, t_so_long *so_long);
void	ft_init_map(t_so_long *so_long);
void	ft_create_map(char *path, t_so_long *so_long);
void	ft_check_map(t_so_long *so_long);
void	ft_init_window(t_so_long *so_long);
void	ft_init_images(t_so_long *so_long);

int		handle_resize(t_so_long *so_long);
int		handle_keypress(int keysym, t_so_long *so_long);
int		handle_btnrealease(t_so_long *so_long);
int		render(t_so_long *so_long);
void	loop_images(t_so_long so_long);
void	destroy_images(t_so_long *so_long);
void	ft_move_player(t_so_long *so_long, int direction);
void	ft_free(char **tab);

#endif