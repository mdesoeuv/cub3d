/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:13:42 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/02/28 17:41:06 by vchevill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void
	ft_incr_pass_block(t_cub3d *cub3d, double v_dy_length, double v_dx_length, double angle)
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

/*
void	put_pixel_to_image_2d(t_cub3d *cub3d, int pos_x, int pos_y, int color)
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

void	draw_map(t_cub3d *cub3d)
{
	int	x;
	int	y;

	y = 0;
	while (y < cub3d->win_height)
	{
		x = 0;
		while (x < cub3d->win_width)
		{
			if (y % CUB_SIZE == 0 || x % CUB_SIZE == 0)
				put_pixel_to_image_2d(cub3d, x, y, create_trgb(0, 255, 0, 0));
			else if (cub3d->map.map[y / CUB_SIZE][x / CUB_SIZE] == '1')
				put_pixel_to_image_2d(cub3d, x, y, create_trgb(0, 0, 0, 0));
			else
				put_pixel_to_image_2d(cub3d, x, y, create_trgb(0, 255, 255, 255));
			(x)++;
		}
		(y)++;
	}
}

void	draw_rays(t_cub3d *cub3d)
{
	int		l;
	double	ray_length;
	double	dx;
	double	dy;
	int		i;
	double	angle_tmp;

	i = -500;
	while ( i < 500)
	{
		angle_tmp = cub3d->player_angle + M_PI / 1980 * i;
		if (angle_tmp > 2 * M_PI)
			angle_tmp -= 2 * M_PI;
		ray_length = ft_ray_length(cub3d, angle_tmp);
		 // dprintf(1, "%f\n", ray_length);
		 // dprintf(1, "-------\n");
		l = 1;
		while (l < ray_length)
		{
			dx = l * cos(angle_tmp);
			dy = l * sin(angle_tmp);
			put_pixel_to_image_2d(cub3d, cub3d->player.x + dx, cub3d->player.y + dy, create_trgb(0, 0, 0, 255));
			l++;
		}
		i++;
	}
}

void	draw_player(t_cub3d *cub3d)
{
	int		l;
	double	dx;
	double	dy;

	put_pixel_to_image_2d(cub3d, cub3d->player.x, cub3d->player.y, create_trgb(0, 0, 0, 255));
	put_pixel_to_image_2d(cub3d, cub3d->player.x, cub3d->player.y + 1, create_trgb(0, 0, 0, 255));
	put_pixel_to_image_2d(cub3d, cub3d->player.x, cub3d->player.y - 1, create_trgb(0, 0, 0, 255));
	put_pixel_to_image_2d(cub3d, cub3d->player.x + 1, cub3d->player.y, create_trgb(0, 0, 0, 255));
	put_pixel_to_image_2d(cub3d, cub3d->player.x + 1, cub3d->player.y + 1, create_trgb(0, 0, 0, 255));
	put_pixel_to_image_2d(cub3d, cub3d->player.x + 1, cub3d->player.y - 1, create_trgb(0, 0, 0, 255));
	put_pixel_to_image_2d(cub3d, cub3d->player.x - 1, cub3d->player.y, create_trgb(0, 0, 0, 255));
	put_pixel_to_image_2d(cub3d, cub3d->player.x - 1, cub3d->player.y + 1, create_trgb(0, 0, 0, 255));
	put_pixel_to_image_2d(cub3d, cub3d->player.x - 1, cub3d->player.y - 1, create_trgb(0, 0, 0, 255));
	l = 1;
	while (l < 11)
	{
		dx = l * cos(cub3d->player_angle);
		dy = l * sin(cub3d->player_angle);
		put_pixel_to_image_2d(cub3d, cub3d->player.x + dx, cub3d->player.y + dy, create_trgb(0, 0, 0, 255));
		l++;
	}
}

void	draw_image_2d(t_cub3d *cub3d)
{
	draw_map(cub3d);
	draw_player(cub3d);
	draw_rays(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->window_ptr, \
		cub3d->render_3d.ptr, 0, 0);
}*/