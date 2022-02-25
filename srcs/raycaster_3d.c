/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_3d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 10:13:32 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/02/25 10:36:39 by vchevill         ###   ########.fr       */
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

double static	ft_increment_ray_absolute_angle(t_cub3d *cub3d, double ray_abs_angle)
{
	ray_abs_angle += cub3d->fov / WINDOW_WIDTH;
	if (ray_abs_angle > 2 * M_PI)
		ray_abs_angle -= 2 * M_PI;
	return (ray_abs_angle);
}

int static		ft_fish_eye_correction(double player_angle, double ray_abs_angle, double ray_length)
{
	double  ray_relative_angle;
	
	ray_relative_angle = fabs(player_angle) - fabs(ray_abs_angle);
		if (ray_relative_angle < 0)
			ray_relative_angle += 2 * M_PI;
		if (ray_relative_angle > 2 * M_PI)
			ray_relative_angle -= 2 * M_PI;
		ray_length = ray_length * cos(ray_relative_angle);
	return (ray_length);
}

void	draw_rays_3d(t_cub3d *cub3d)
{
	int		column;
	double	ray_length;
	int		x;
	double	ray_abs_angle;
	double	wall_size;
	int		y;
	int		offset_y;
	int		offset_x;

	double	ratio;
	int		y_wall;
	int		x_wall;

	offset_y = WINDOW_HEIGHT / 2;
	offset_x = WINDOW_WIDTH / 2;
	x = 0;
	x_wall = -1;
	ray_abs_angle = (cub3d->player_angle - (cub3d->fov / 2)) - (cub3d->fov / WINDOW_WIDTH);
	while (x < WINDOW_WIDTH)
	{
		if (cub3d->newWall)
			x_wall = -1;
		x_wall++;
		ray_abs_angle = ft_increment_ray_absolute_angle(cub3d, ray_abs_angle);
		ray_length = ft_fish_eye_correction(cub3d->player_angle, ray_abs_angle, ft_ray_length(cub3d, ray_abs_angle));		
		wall_size = cub3d->slice_ratio / ray_length;
		if (wall_size > WINDOW_HEIGHT)//a retirer apres
			wall_size = WINDOW_HEIGHT;
		column = (x - offset_x) + (WINDOW_WIDTH / 2);
		y = -1;
		while (++y < offset_y - wall_size / 2)
			put_pixel_to_image_3d(cub3d, column, y, create_trgb(0, cub3d->color_ceiling[0], cub3d->color_ceiling[1], cub3d->color_ceiling[2]));
		y_wall = -1;
		while (y < wall_size / 2 + offset_y)
		{
			y_wall++;
			if (cub3d->map.ray_has_hit_x == 0  && ray_abs_angle > M_PI / 2 && ray_abs_angle < (3 * M_PI)/2)
			{
				ratio = wall_size / cub3d->texture_e.height;
				ft_pixel_texture_color(cub3d, cub3d->texture_e, ft_texture_x_offset(cub3d, ray_abs_angle, ray_length) / ratio, y_wall / ratio);
				put_pixel_to_image_3d(cub3d, column, y, create_trgb(0, cub3d->color_texture[0], cub3d->color_texture[1], cub3d->color_texture[2]));
			}
			else if (cub3d->map.ray_has_hit_x == 0)
			{
				ratio = wall_size / cub3d->texture_w.height;
				dprintf(1, "%d\n", ((int)(fabs(ray_length * sin(ray_abs_angle)) - (CUBE_SIZE - (cub3d->player.x % CUBE_SIZE)) % CUBE_SIZE)));
				ft_pixel_texture_color(cub3d, cub3d->texture_w,  ft_texture_x_offset(cub3d, ray_abs_angle, ray_length) / ratio, y_wall / ratio);
				put_pixel_to_image_3d(cub3d, column, y, create_trgb(0, cub3d->color_texture[0], cub3d->color_texture[1], cub3d->color_texture[2]));
			}
			else if (cub3d->map.ray_has_hit_x == 1  && ray_abs_angle > 0 && ray_abs_angle < M_PI)
			{
				ratio = wall_size / cub3d->texture_n.height;
				ft_pixel_texture_color(cub3d, cub3d->texture_n,  ft_texture_x_offset(cub3d, ray_abs_angle, ray_length) / ratio, y_wall / ratio);
				put_pixel_to_image_3d(cub3d, column, y, create_trgb(0, cub3d->color_texture[0], cub3d->color_texture[1], cub3d->color_texture[2]));
			}
			else
			{
				ratio = wall_size / cub3d->texture_s.height;
				ft_pixel_texture_color(cub3d, cub3d->texture_s,  ft_texture_x_offset(cub3d, ray_abs_angle, ray_length) / ratio, y_wall / ratio);
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