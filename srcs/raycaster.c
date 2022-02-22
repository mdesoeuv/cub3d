/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:13:42 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/02/22 14:22:30 by vchevill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	create_trgb(unsigned char t, unsigned char r, \
	unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

void	put_pixel_to_image(t_cub3d *cub3d, int pos_x, int pos_y, int color)
{
	unsigned char	*tab;

	tab = (unsigned char *)&color;
	cub3d->win_render.data[pos_y * cub3d->win_render.line_size + \
		pos_x * cub3d->win_render.bits_per_pixel / 8] = tab[0];
	cub3d->win_render.data[(pos_y * cub3d->win_render.line_size + \
		pos_x * cub3d->win_render.bits_per_pixel / 8) + 1] = tab[1];
	cub3d->win_render.data[(pos_y * cub3d->win_render.line_size + \
		pos_x * cub3d->win_render.bits_per_pixel / 8) + 2] = tab[2];
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
			if (y % CUBE_SIZE == 0 || x % CUBE_SIZE == 0)
				put_pixel_to_image(cub3d, x, y, create_trgb(0, 255, 0, 0));
			else if (cub3d->map.map[y / CUBE_SIZE][x / CUBE_SIZE] == '1')
				put_pixel_to_image(cub3d, x, y, create_trgb(0, 0, 0, 0));
			else
				put_pixel_to_image(cub3d, x, y, create_trgb(0, 255, 255, 255));
			(x)++;
		}
		(y)++;
	}
}

void	draw_image(t_cub3d *cub3d)
{
	draw_map(cub3d);
	draw_player(cub3d);
	draw_rays(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->window_ptr, \
		cub3d->win_render.pointer, 0, 0);
}

void	draw_rays(t_cub3d *cub3d)
{
	int		l;
	double	dx;
	double	dy;

	l = 1;
	while (l < 11)
	{
		dx = l * cos(cub3d->player_angle);
		dy = l * sin(cub3d->player_angle);
		put_pixel_to_image(cub3d, cub3d->player.x + dx, cub3d->player.y + dy, create_trgb(0, 0, 0, 255));
		l++;
	}
}

void	draw_player(t_cub3d *cub3d)
{
	int		l;
	double	dx;
	double	dy;

	put_pixel_to_image(cub3d, cub3d->player.x, cub3d->player.y, create_trgb(0, 0, 0, 255));
	put_pixel_to_image(cub3d, cub3d->player.x, cub3d->player.y + 1, create_trgb(0, 0, 0, 255));
	put_pixel_to_image(cub3d, cub3d->player.x, cub3d->player.y - 1, create_trgb(0, 0, 0, 255));
	put_pixel_to_image(cub3d, cub3d->player.x + 1, cub3d->player.y, create_trgb(0, 0, 0, 255));
	put_pixel_to_image(cub3d, cub3d->player.x + 1, cub3d->player.y + 1, create_trgb(0, 0, 0, 255));
	put_pixel_to_image(cub3d, cub3d->player.x + 1, cub3d->player.y - 1, create_trgb(0, 0, 0, 255));
	put_pixel_to_image(cub3d, cub3d->player.x - 1, cub3d->player.y, create_trgb(0, 0, 0, 255));
	put_pixel_to_image(cub3d, cub3d->player.x - 1, cub3d->player.y + 1, create_trgb(0, 0, 0, 255));
	put_pixel_to_image(cub3d, cub3d->player.x - 1, cub3d->player.y - 1, create_trgb(0, 0, 0, 255));
	l = 1;
	while (l < 11)
	{
		dx = l * cos(cub3d->player_angle);
		dy = l * sin(cub3d->player_angle);
		put_pixel_to_image(cub3d, cub3d->player.x + dx, cub3d->player.y + dy, create_trgb(0, 0, 0, 255));
		l++;
	}
}

void	ft_rendering(t_cub3d *cub3d)
{
	draw_image(cub3d);
	mlx_hook(cub3d->window_ptr, 02, 1L << 0, &handle_keypress, cub3d);
	mlx_hook(cub3d->window_ptr, 17, 0L,
		&handle_btnrealease, cub3d);
	mlx_loop(cub3d->mlx);
}
