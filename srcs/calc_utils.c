/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 10:21:43 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/02/25 14:56:05 by vchevill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/cub3d.h"

int	ft_particular_angle(int player_x, double ray_abs_angle)
{
	if (ray_abs_angle == M_PI / 2 || ray_abs_angle == 3 * M_PI /2)
		return (player_x % CUBE_SIZE);
	else
		return (player_x % CUBE_SIZE);
}

int	ft_texture_x_offset(t_cub3d *cub3d, double ray_abs_angle, double ray_length)
{
	double	alpha;
	if (ray_abs_angle > 0 && ray_abs_angle < (M_PI / 2))
	{
		alpha = ray_abs_angle;
		return(CUBE_SIZE - ((int)((ray_length * cos(alpha)) - (CUBE_SIZE - (cub3d->player.x % CUBE_SIZE))) % CUBE_SIZE));
	}	
	else if (ray_abs_angle > (3 * M_PI / 2) && ray_abs_angle < 2 * M_PI)
	{
		alpha = 2 * M_PI - ray_abs_angle;
		return(CUBE_SIZE - ((int)(ray_length * cos(alpha) - (CUBE_SIZE - (cub3d->player.x % CUBE_SIZE))) % CUBE_SIZE));
	}
	else if (ray_abs_angle > M_PI / 2 && ray_abs_angle < M_PI)
	{
		alpha = M_PI - ray_abs_angle;
		return(int)((ray_length * cos(alpha)) - (cub3d->player.x % CUBE_SIZE));
	}
	else if (ray_abs_angle > M_PI && ray_abs_angle < 3 * M_PI / 2)
	{
		alpha = ray_abs_angle - M_PI;
		return(int)((ray_length * cos(alpha)) - (cub3d->player.x % CUBE_SIZE));
	}
	else
		return (ft_particular_angle(cub3d->player.x, ray_abs_angle));
}

int	ft_texture_y_offset(t_cub3d *cub3d, double ray_abs_angle, double ray_length)
{
	double	alpha;
	if (ray_abs_angle > M_PI / 2 && ray_abs_angle < (M_PI))
	{
		alpha = ray_abs_angle - M_PI;
				return((int)((ray_length * sin(alpha)) - (cub3d->player.y % CUBE_SIZE)) % CUBE_SIZE);// droite fond

	}	
	else if (ray_abs_angle > (0) && ray_abs_angle < M_PI / 2)
	{
		alpha = ray_abs_angle;
		return(CUBE_SIZE - ((int)(ray_length * sin(alpha) - (CUBE_SIZE - (cub3d->player.y % CUBE_SIZE))) % CUBE_SIZE) % CUBE_SIZE);// mur gauche devant
	}
	else if (ray_abs_angle > M_PI && ray_abs_angle < 3 * M_PI / 2)
	{
		alpha = M_PI - ray_abs_angle;
				return(CUBE_SIZE - ((int)((ray_length * sin(alpha)) - (CUBE_SIZE - (cub3d->player.y % CUBE_SIZE))) % CUBE_SIZE) % CUBE_SIZE);// droite devant

	}
	else if (ray_abs_angle > 3 * M_PI / 2 && ray_abs_angle < 2 * M_PI)
	{
		alpha = 2 * M_PI - ray_abs_angle;
		return((int)((ray_length * sin(alpha)) - (cub3d->player.y % CUBE_SIZE)) % CUBE_SIZE);// mur gauche derrier
	}
	else
		return (ft_particular_angle(cub3d->player.y, ray_abs_angle));
}