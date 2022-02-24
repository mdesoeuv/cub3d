/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_3d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 10:13:32 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/02/24 10:21:27 by mdesoeuv         ###   ########lyon.fr   */
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

void	draw_rays_3d(t_cub3d *cub3d)
{
	int		column;
	double	ray_length;
	int		x;
	double	angle_tmp;
	double	wall_size;
	int		y;
	int		offset_y;
	int		offset_x;
	double  angle_diff;
	double	ratio;
	int		y_wall;

	offset_y = WINDOW_HEIGHT / 2;
	offset_x = WINDOW_WIDTH / 2;
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		angle_tmp = cub3d->player_angle + M_PI / (WINDOW_WIDTH * 2.5) * (x - offset_x);
		if (angle_tmp > 2 * M_PI)
			angle_tmp -= 2 * M_PI;
		ray_length = ft_ray_length(cub3d, angle_tmp);
		angle_diff = cub3d->player_angle - angle_tmp;
		if (angle_diff < 0)
			angle_diff += 2 * M_PI;
		if (angle_diff > 2 * M_PI)
			angle_diff -= 2 * M_PI;
		ray_length = ray_length * cos(angle_diff);
		wall_size = (WINDOW_HEIGHT * 40) / ray_length;
		if (wall_size > WINDOW_HEIGHT)
			wall_size = WINDOW_HEIGHT;
		column = (x - offset_x) + (WINDOW_WIDTH / 2);
		y = -1;
		while (++y < offset_y - wall_size / 2)
			put_pixel_to_image_3d(cub3d, column, y, create_trgb(0, cub3d->color_ceiling[0], cub3d->color_ceiling[1], cub3d->color_ceiling[2]));
		y_wall = -1;
		while (y < wall_size / 2 + offset_y)
		{
			y_wall++;
			if (cub3d->map.ray_hit_x == 1  && angle_tmp > M_PI / 2 && angle_tmp < (3 * M_PI)/2)
			{
				ratio = wall_size / cub3d->texture_e.height;
				ft_pixel_texture_color(cub3d, cub3d->texture_e, x / ratio, y_wall / ratio);
				put_pixel_to_image_3d(cub3d, column, y, create_trgb(0, cub3d->color_texture[0], cub3d->color_texture[1], cub3d->color_texture[2]));
			}
			else if (cub3d->map.ray_hit_x == 1)
			{
				ratio = wall_size / cub3d->texture_n.height;
				ft_pixel_texture_color(cub3d, cub3d->texture_n, x / ratio, y_wall / ratio);
				put_pixel_to_image_3d(cub3d, column, y, create_trgb(0, cub3d->color_texture[0], cub3d->color_texture[1], cub3d->color_texture[2]));
			}
			else if (cub3d->map.ray_hit_x == 0  && angle_tmp > 0 && angle_tmp < M_PI)
			{
				ratio = wall_size / cub3d->texture_s.height;
				ft_pixel_texture_color(cub3d, cub3d->texture_s, x / ratio, y_wall / ratio);
				put_pixel_to_image_3d(cub3d, column, y, create_trgb(0, cub3d->color_texture[0], cub3d->color_texture[1], cub3d->color_texture[2]));
			}
			else
			{
				ratio = wall_size / cub3d->texture_w.height;
				ft_pixel_texture_color(cub3d, cub3d->texture_w, x / ratio, y_wall / ratio);
				put_pixel_to_image_3d(cub3d, column, y, create_trgb(0, cub3d->color_texture[0], cub3d->color_texture[1], cub3d->color_texture[2]));
			}
			y++;
		}
		while (y < WINDOW_HEIGHT)
			put_pixel_to_image_3d(cub3d, column, y++, create_trgb(0, cub3d->color_ground[0], cub3d->color_ground[1], cub3d->color_ground[2]));
		x++;
	}
}


void	draw_image_3d(t_cub3d *cub3d)
{
	mlx_destroy_image(cub3d->mlx, cub3d->render_3d.ptr);
	cub3d->render_3d.ptr = mlx_new_image(cub3d->mlx, cub3d->win_width, \
		cub3d->win_height);
	cub3d->render_3d.data = mlx_get_data_addr(cub3d->render_3d.ptr, \
		&(cub3d->render_3d.bits_per_pixel), &(cub3d->render_3d.line_size), \
		&(cub3d->render_3d.endian));
	draw_rays_3d(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->window_ptr, \
		cub3d->render_3d.ptr, 0, 0);
}