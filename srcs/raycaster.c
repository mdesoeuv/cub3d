/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:13:42 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/02/22 10:47:51 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

void	put_pixel_to_image(t_cub3d *cub3d, int pos_x, int pos_y, int color)
{
	unsigned char	*tab;

	tab = (unsigned char *)&color;
	cub3d->win_render.data[pos_y * cub3d->win_render.line_size + pos_x * cub3d->win_render.bits_per_pixel / 8] = tab[0];
	cub3d->win_render.data[(pos_y * cub3d->win_render.line_size + pos_x * cub3d->win_render.bits_per_pixel / 8) + 1] = tab[1];
	cub3d->win_render.data[(pos_y * cub3d->win_render.line_size + pos_x * cub3d->win_render.bits_per_pixel / 8) + 2] = tab[2];
}

void	draw_image(t_cub3d *cub3d, char **map)
{
	t_pos	pos;

	pos.y = 0;
	while (pos.y < cub3d->win_height)
	{
		pos.x = 0;
		while (pos.x < cub3d->win_width)
		{
			if (pos.y % CUBE_SIZE == 0 || pos.x % CUBE_SIZE == 0)
				put_pixel_to_image(cub3d, pos.x, pos.y, create_trgb(0, 255, 0, 0));
			else if (map[pos.y / CUBE_SIZE][pos.x / CUBE_SIZE] == '1')
				put_pixel_to_image(cub3d, pos.x, pos.y, create_trgb(0, 0, 0, 0));
			else
				put_pixel_to_image(cub3d, pos.x, pos.y, create_trgb(0, 255, 255, 255));
			(pos.x)++;
		}
		(pos.y)++;
	}
	draw_player(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->window_ptr, cub3d->win_render.pointer, 0, 0);
}

void	create_map_image(t_cub3d *cub3d)
{
	cub3d->win_render.pointer = mlx_new_image(cub3d->mlx, cub3d->win_width, cub3d->win_height);
	cub3d->win_render.data = mlx_get_data_addr(cub3d->win_render.pointer, &(cub3d->win_render.bits_per_pixel), &(cub3d->win_render.line_size), &(cub3d->win_render.endian));
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

void	draw_tests(t_cub3d *cub3d)
{
	draw_image(cub3d, cub3d->map.map);
	mlx_hook(cub3d->window_ptr, 02, 1L << 0, &handle_keypress, cub3d);
	mlx_hook(cub3d->window_ptr, 17, 0L,
		&handle_btnrealease, cub3d);
	mlx_loop(cub3d->mlx);
}
