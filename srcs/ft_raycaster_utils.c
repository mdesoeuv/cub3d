/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycaster_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:42:02 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/28 17:42:29 by vchevill         ###   ########.fr       */
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

double	ft_fish_eye_correction(double player_angle,
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