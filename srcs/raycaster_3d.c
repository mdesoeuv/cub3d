/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_3d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 10:13:32 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/02/28 17:32:29 by vchevill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel_to_image_3d(t_cub3d *cub3d, int pos_x, int pos_y, int color)
{
	unsigned char	*tab;

	tab = (unsigned char *)&color;
	cub3d->render_3d.data[pos_y * cub3d->render_3d.line_size + \
		pos_x * cub3d->render_3d.bits_per_pixel / 8] = tab[0];
	cub3d->render_3d.data[(pos_y * cub3d->render_3d.line_size + \
		pos_x * cub3d->render_3d.bits_per_pixel / 8) + 1] = tab[1];
	cub3d->render_3d.data[(pos_y * cub3d->render_3d.line_size + \
		pos_x * cub3d->render_3d.bits_per_pixel / 8) + 2] = tab[2];
}

double	ft_increment_ray_absolute_angle(t_cub3d *cub3d, double ray_abs_angle)
{
	ray_abs_angle += cub3d->fov / WINDOW_WIDTH;
	if (ray_abs_angle > 2 * M_PI)
		ray_abs_angle -= 2 * M_PI;
	else if (ray_abs_angle < 0)
		ray_abs_angle += 2 * M_PI;
	return (ray_abs_angle);
}

int	create_trgb(unsigned char t, unsigned char r, \
	unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

double static	ft_fish_eye_correction(double player_angle,
			double ray_abs_angle, double ray_length)
{
	double	ray_relative_angle;

	if (player_angle > ray_abs_angle)
		ray_relative_angle = player_angle - ray_abs_angle;
	else
		ray_relative_angle = ray_abs_angle - player_angle;
	ray_length = ray_length * cos(ray_relative_angle);
	return (ray_length);
}

static void	ft_get_pixel_in_texture(t_cub3d *cub3d, int y_wind,
		double x_wind, t_image texture)
{
	double	y_ratio;
	double	x_ratio;

	y_ratio = cub3d->wall_size / texture.height;
	x_ratio = (double)CUB_SIZE / (double)texture.width;
	if (texture.orientation == 'n' || texture.orientation == 's')
	{
		ft_pixel_texture_color(cub3d, texture, ((CUB_SIZE
					+ ft_texture_x_offset(cub3d, cub3d->ray_abs_angle))
				% CUB_SIZE) / x_ratio,
			(cub3d->y_wall + cub3d->y_wall_offset) / y_ratio);
		put_pixel_to_image_3d(cub3d, x_wind, y_wind,
			create_trgb(0, cub3d->color_texture[0],
				cub3d->color_texture[1], cub3d->color_texture[2]));
	}	
	else
	{
		ft_pixel_texture_color(cub3d, texture, ((CUB_SIZE
					+ ft_texture_y_offset(cub3d, cub3d->ray_abs_angle))
				% CUB_SIZE) / x_ratio,
			(cub3d->y_wall + cub3d->y_wall_offset) / y_ratio);
		put_pixel_to_image_3d(cub3d, x_wind, y_wind,
			create_trgb(0, cub3d->color_texture[0],
				cub3d->color_texture[1], cub3d->color_texture[2]));
	}
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

void	draw_rays_3d(t_cub3d *cub3d)
{
	int		x_wind;

	x_wind = 0;
	cub3d->ray_abs_angle = (cub3d->player_angle - (cub3d->fov / 2))
		- (cub3d->fov / WINDOW_WIDTH);
	while (x_wind < WINDOW_WIDTH)
	{
		cub3d->ray_abs_angle =
			ft_increment_ray_absolute_angle(cub3d, cub3d->ray_abs_angle);
		cub3d->ray_length = ft_ray_length(cub3d, cub3d->ray_abs_angle);
		ft_draw_vertical_line(cub3d, x_wind);
		x_wind++;
	}
}

void	draw_image_3d(t_cub3d *cub3d)
{
	draw_rays_3d(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->window_ptr, \
		cub3d->render_3d.ptr, 0, 0);
}
