/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 10:21:43 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/02/28 15:22:57 by vchevill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/cub3d.h"

int	ft_particular_angle(int player_x, double ray_abs_angle)
{
	if (ray_abs_angle == M_PI / 2 || ray_abs_angle == 3 * M_PI / 2)
		return (player_x % CUBE_SIZE);
	else
		return (player_x % CUBE_SIZE);
}

double static	ft_calc_alpha_x(double ray_abs_angle)
{
	if (ray_abs_angle > 0 && ray_abs_angle < (M_PI / 2))
		return (ray_abs_angle);
	else if (ray_abs_angle > (3 * M_PI / 2) && ray_abs_angle < 2 * M_PI)
		return (2 * M_PI - ray_abs_angle);
	else if (ray_abs_angle > M_PI / 2 && ray_abs_angle < M_PI)
		return ( M_PI - ray_abs_angle);
	else if (ray_abs_angle > M_PI && ray_abs_angle < 3 * M_PI / 2)
		return (ray_abs_angle - M_PI);
	return (ray_abs_angle);
}

int	ft_texture_x_offset(t_cub3d *cub3d, double ray_abs_angle, double ray_length)
{
	double	alpha;

	alpha = ft_calc_alpha_x(ray_abs_angle);
	if (ray_abs_angle > 0 && ray_abs_angle < (M_PI / 2))
		return (CUBE_SIZE - ((int)((ray_length * cos(alpha))
				- (CUBE_SIZE - (cub3d->player.x % CUBE_SIZE))) % CUBE_SIZE));
	else if (ray_abs_angle > (3 * M_PI / 2) && ray_abs_angle < 2 * M_PI)
		return (CUBE_SIZE - ((int)(ray_length * cos(alpha)
				- (CUBE_SIZE - (cub3d->player.x % CUBE_SIZE))) % CUBE_SIZE));
	else if (ray_abs_angle > M_PI / 2 && ray_abs_angle < M_PI)
		return ((int)((ray_length * cos(alpha))
			- (cub3d->player.x % CUBE_SIZE)));
	else if (ray_abs_angle > M_PI && ray_abs_angle < 3 * M_PI / 2)
		return ((int)((ray_length * cos(alpha))
			- (cub3d->player.x % CUBE_SIZE)));
	else
		return (ft_particular_angle(cub3d->player.x, ray_abs_angle));
}

double static	ft_calc_alpha_y(double ray_abs_angle)
{
	if (ray_abs_angle > M_PI / 2 && ray_abs_angle < (M_PI))
		return (ray_abs_angle - M_PI);
	else if (ray_abs_angle > (0) && ray_abs_angle < M_PI / 2)
		return (ray_abs_angle);
	else if (ray_abs_angle > M_PI && ray_abs_angle < 3 * M_PI / 2)
		return (M_PI - ray_abs_angle);
	else if (ray_abs_angle > 3 * M_PI / 2 && ray_abs_angle < 2 * M_PI)
		return (2 * M_PI - ray_abs_angle);
	else
		return (ray_abs_angle);
}

int	ft_texture_y_offset(t_cub3d *cub3d, double ray_abs_angle, double ray_length)
{
	double	alpha;

	alpha = ft_calc_alpha_y(ray_abs_angle);
	if (ray_abs_angle > M_PI / 2 && ray_abs_angle < (M_PI))
		return ((int)((ray_length * sin(alpha))
			- (cub3d->player.y % CUBE_SIZE)) % CUBE_SIZE);
	else if (ray_abs_angle > (0) && ray_abs_angle < M_PI / 2)
		return (CUBE_SIZE - ((int)(ray_length * sin(alpha)
				- (CUBE_SIZE - (cub3d->player.y % CUBE_SIZE))) % CUBE_SIZE));
	else if (ray_abs_angle > M_PI && ray_abs_angle < 3 * M_PI / 2)
		return (CUBE_SIZE - ((int)((ray_length * sin(alpha))
				- (CUBE_SIZE - (cub3d->player.y % CUBE_SIZE))) % CUBE_SIZE));
	else if (ray_abs_angle > 3 * M_PI / 2 && ray_abs_angle < 2 * M_PI)
		return ((int)((ray_length * sin(alpha))
			- (cub3d->player.y % CUBE_SIZE)) % CUBE_SIZE);
	else
		return (ft_particular_angle(cub3d->player.y, ray_abs_angle));
}
