/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:13:42 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/03/15 11:29:20 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void
	ft_incr_pass_block(t_cub3d *cub3d, double v_dy_length,
		double v_dx_length, double angle)
{
	if (v_dy_length > v_dx_length
		&& !(angle > M_PI / 2 && angle < (3 * M_PI) / 2))
	{
		cub3d->ray_has_hit_y = 1;
		cub3d->pass_block_x++;
	}
	else if (v_dy_length > v_dx_length)
	{
		cub3d->pass_block_x--;
		cub3d->ray_has_hit_y = 1;
	}
	else if (v_dy_length < v_dx_length && !(angle > 0 && angle < M_PI))
	{
		cub3d->pass_block_y--;
		cub3d->ray_has_hit_y = 0;
	}
	else
	{
		cub3d->pass_block_y++;
		cub3d->ray_has_hit_y = 0;
	}
}

static double	ft_longest_vector(double v_dy_length, double v_dx_length)
{
	if (v_dy_length > v_dx_length)
		return (v_dx_length);
	else
		return (v_dy_length);
}

double	ft_ray_length(t_cub3d *cub3d, double angle)
{
	double		v_dy_length;
	double		v_dx_length;

	cub3d->pass_block_x = 0;
	cub3d->pass_block_y = 0;
	cub3d->ray_has_hit_y = -1;
	while (cub3d->map.map[(cub3d->player.y / CUB_SIZE) + cub3d->pass_block_y]
		[(cub3d->player.x / CUB_SIZE) + cub3d->pass_block_x] != '1')
	{
		if (angle > 0 && angle < M_PI && cub3d->ray_has_hit_y != 1)
			v_dy_length = fabs((CUB_SIZE - (cub3d->player.y % CUB_SIZE)
						+ (CUB_SIZE * abs(cub3d->pass_block_y))) / sin(angle));
		else if (cub3d->ray_has_hit_y != 1)
			v_dy_length = fabs(((cub3d->player.y % CUB_SIZE)
						+ (CUB_SIZE * abs(cub3d->pass_block_y))) / sin(angle));
		if (angle > M_PI / 2 && angle < (3 * M_PI) / 2
			&& cub3d->ray_has_hit_y != 0)
			v_dx_length = fabs(((cub3d->player.x % CUB_SIZE)
						+ (CUB_SIZE * abs(cub3d->pass_block_x))) / cos(angle));
		else if (cub3d->ray_has_hit_y != 0)
			v_dx_length = fabs((CUB_SIZE - (cub3d->player.x % CUB_SIZE)
						+ (CUB_SIZE * abs(cub3d->pass_block_x))) / cos(angle));
		ft_incr_pass_block(cub3d, v_dy_length, v_dx_length, angle);
	}
	return (ft_longest_vector(v_dy_length, v_dx_length));
}

void	ft_rendering(t_cub3d *cub3d)
{
	ft_draw_image(cub3d);
	mlx_hook(cub3d->window_ptr, 02, 1L << 0, &handle_keypress, cub3d);
	mlx_hook(cub3d->window_ptr, 17, 0L,
		&handle_btnrealease, cub3d);
	mlx_loop(cub3d->mlx);
}
