/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_3d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 10:13:32 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/03/01 11:39:12 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ft_get_pixel_in_texture(t_cub3d *cub3d, int y_wind,
		double x_wind, t_image texture)
{
	double	y_ratio;
	double	x_ratio;

	y_ratio = cub3d->wall_size / texture.height;
	x_ratio = (double)CUB_SIZE / (double)texture.width;
	if (texture.orientation == 'n' || texture.orientation == 's')
		ft_pixel_texture_color(cub3d, texture, ((CUB_SIZE
					+ ft_texture_x_offset(cub3d, cub3d->ray_abs_angle))
				% CUB_SIZE) / x_ratio,
			(cub3d->y_wall + cub3d->y_wall_offset) / y_ratio);
	else
		ft_pixel_texture_color(cub3d, texture, ((CUB_SIZE
					+ ft_texture_y_offset(cub3d, cub3d->ray_abs_angle))
				% CUB_SIZE) / x_ratio,
			(cub3d->y_wall + cub3d->y_wall_offset) / y_ratio);
	put_pixel_to_image_3d(cub3d, x_wind, y_wind,
		create_trgb(0, cub3d->color_texture[0],
			cub3d->color_texture[1], cub3d->color_texture[2]));
}

static void	ft_draw_wall(t_cub3d *cub3d, int y_wind,
		double x_wind)
{
	cub3d->y_wall_offset = 0;
	if (cub3d->wall_size > WINDOW_HEIGHT)
		cub3d->y_wall_offset = (cub3d->wall_size - WINDOW_HEIGHT) / 2;
	cub3d->y_wall++;
	if (cub3d->ray_has_hit_y == 1 && cub3d->ray_abs_angle > M_PI / 2
		&& cub3d->ray_abs_angle < (3 * M_PI) / 2)
		ft_get_pixel_in_texture(cub3d, y_wind, x_wind, cub3d->texture_e);
	else if (cub3d->ray_has_hit_y == 1)
		ft_get_pixel_in_texture(cub3d, y_wind, x_wind, cub3d->texture_w);
	else if (cub3d->ray_has_hit_y == 0 && cub3d->ray_abs_angle > 0
		&& cub3d->ray_abs_angle < M_PI)
		ft_get_pixel_in_texture(cub3d, y_wind, x_wind, cub3d->texture_n);
	else
		ft_get_pixel_in_texture(cub3d, y_wind, x_wind, cub3d->texture_s);
}

static void	ft_draw_vertical_line(t_cub3d *cub3d, double x_wind)
{
	int		y_wind;
	double	ray_length_fish_eye_correc;
	int		offset_y;

	y_wind = -1;
	offset_y = WINDOW_HEIGHT / 2;
	ray_length_fish_eye_correc = ft_fish_eye_correction
		(cub3d->player_angle, cub3d->ray_abs_angle, cub3d->ray_length);
	cub3d->wall_size = (cub3d->player_dist / ray_length_fish_eye_correc)
		* CUB_SIZE;
	while (++y_wind < offset_y - cub3d->wall_size / 2)
		put_pixel_to_image_3d(cub3d, x_wind, y_wind, create_trgb(0,
				cub3d->color_ceiling[0], cub3d->color_ceiling[1],
				cub3d->color_ceiling[2]));
	cub3d->y_wall = -1;
	while (y_wind < cub3d->wall_size / 2 + offset_y && y_wind < WINDOW_HEIGHT)
		ft_draw_wall(cub3d, y_wind++, x_wind);
	while (y_wind < WINDOW_HEIGHT)
		put_pixel_to_image_3d(cub3d, x_wind, y_wind++, create_trgb(0,
				cub3d->color_ground[0], cub3d->color_ground[1],
				cub3d->color_ground[2]));
}

// x_wind créé en tant que int et appelé en tant que double dans les fonctions suivantes ?
void	ft_draw_image(t_cub3d *cub3d)
{
	int		x_wind;

	x_wind = 0;
	cub3d->ray_abs_angle = (cub3d->player_angle - (cub3d->fov / 2))
		- (cub3d->fov / WINDOW_WIDTH);
	while (x_wind < WINDOW_WIDTH)
	{
		cub3d->ray_abs_angle
			= ft_increment_ray_absolute_angle(cub3d, cub3d->ray_abs_angle);
		cub3d->ray_length = ft_ray_length(cub3d, cub3d->ray_abs_angle);
		ft_draw_vertical_line(cub3d, x_wind);
		x_wind++;
	}
	mlx_put_image_to_window(cub3d->mlx, cub3d->window_ptr, \
		cub3d->render_3d.ptr, 0, 0);
}
