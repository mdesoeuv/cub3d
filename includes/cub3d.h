/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 09:54:12 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/28 15:56:29 by vchevill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
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
the .cub extension.\n"
# define ERROR_FILE_OPENING "Can't open file given in argument.\n"
# define ERROR_MALLOC "Malloc error. Please free memory space and retry.\n"
# define ERROR_OTHER_CHARS "At least one character in the map is invalid.\
(Not 0, 1, C, E or P)\n"
# define ERROR_MISSING_PLAYER "Need one player.\n"
# define ERROR_TOO_MANY_PLAYERS "Too many players in the map.\n"
# define ERROR_NOT_A_RECTANGLE "The map is not a rectangle.\n"
# define ERROR_MINILIBX "Minilibix usage error.\n"
# define ERROR_EDGES "The edges of the map are invalid (must be walls -1-).\n"
# define ERROR_FILENAME_MISSING "Please pass one filename in parameter.\n"
# define ERROR_MISSING_TEXTURES "At least one texture \
path has not been declared.\n"
# define ERROR_INVALID_TEXTURE_ARG_NAME "Texture declaration error.\n"
# define ERROR_TEXTURE_DEFINED_TWICE "A texture path has been declared twice.\n"
# define ERROR_XPM_INIT "Error while initialised texture. XPM file must be \
corrupted or inaccessible.\n"

# define CUB_SIZE 258
# define MOVE_SIZE 60
# define ANGLE_INC 20
# define FOV 45
# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2
# define ROT_LEFT 123
# define ROT_RIGHT 124
# define ESC 53
# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 768

typedef struct s_image
{
	void	*ptr;
	int		height;
	int		width;
	char	*data;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
}	t_image;

typedef struct s_map
{
	int		fd;
	int		line_count;
	int		longest_line;
	char	direction;
	int		line_start_map_in_cub;
	char	*path;
	char	**map;
}				t_map;

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_cub3d
{
	void	*mlx;
	void	*window_ptr;
	t_pos	player;
	double	player_dist;
	double	fov;
	double	slice_ratio;
	t_image	texture_n;
	t_image	texture_s;
	t_image	texture_w;
	t_image	texture_e;
	int		color_ground[3];
	int		color_ceiling[3];
	int		color_texture[3];
	int		win_height;
	int		win_width;
	int		ray_has_hit_y;
	int		pass_block_x;
	int		pass_block_y;
	double	player_angle;
	t_map	map;
	t_image	render_3d;
}				t_cub3d;

/* PARSING */
void	display_map_and_textures(t_cub3d *cub3d);
void	ft_check_file_extension(char *path, t_cub3d *so_long);
char	**ft_rotate_map(char **map, t_cub3d *cub3d);
void	ft_define_texture(t_cub3d *cub3d, char *line);

/*TEXTURES*/
int		ft_all_textures_declared(t_cub3d *cub3d);
void	get_textures_path(t_cub3d *cub3d);

void	ft_print_error(char *str, t_cub3d *so_long);
void	ft_init_vars(t_cub3d *so_long);
void	ft_create_map(char *path, t_cub3d *so_long);
void	ft_check_map(t_cub3d *so_long);
void	ft_init_window(t_cub3d *so_long);
void	ft_init_images(t_cub3d *so_long);

int		handle_resize(t_cub3d *so_long);
int		handle_keypress(int keysym, t_cub3d *so_long);
int		handle_btnrealease(t_cub3d *so_long);
int		render(t_cub3d *so_long);
void	loop_images(t_cub3d so_long);
void	destroy_images(t_cub3d *so_long);
void	ft_move_player(t_cub3d *so_long, int direction);
int		ft_texture_x_offset(t_cub3d *cub3d, double ray_abs_angle, double ray_length);
int		ft_texture_y_offset(t_cub3d *cub3d, double ray_abs_angle, double ray_length);

/*RAYCASTING*/
void	ft_init_render_image(t_cub3d *cub3d);
void	ft_rendering(t_cub3d *cub3d);
void	draw_player(t_cub3d *cub3d);
void	draw_image_2d(t_cub3d *cub3d);
void	draw_image_3d(t_cub3d *cub3d);
void	put_pixel_to_image(t_cub3d *cub3d, int pos_x, int pos_y, int color);
int		create_trgb(unsigned char t, unsigned char r, \
	unsigned char g, unsigned char b);
double	ft_ray_length(t_cub3d *cub3d, double angle);

void	ft_init_texture(t_cub3d *cub3d, char *texture_path, t_image *image_struc);
void	ft_pixel_texture_color(t_cub3d *cub3d, t_image image, int x, int y);
double	ft_increment_ray_absolute_angle(t_cub3d *cub3d, double ray_abs_angle);
#endif