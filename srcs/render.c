/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:23:32 by vchevill          #+#    #+#             */
/*   Updated: 2022/01/20 14:22:34 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	parse_chars(t_so_long *so_long, int width, int i, int j)
{
	if (so_long->map.map[i][j] == '1')
		mlx_put_image_to_window(so_long->mlx, so_long->win, so_long->img.wall,
			width, i * IMG_SIZE);
	else if (so_long->map.map[i][j] == '0')
		mlx_put_image_to_window(so_long->mlx, so_long->win, so_long->img.ground,
			width, i * IMG_SIZE);
	else if (so_long->map.map[i][j] == 'P')
		mlx_put_image_to_window(so_long->mlx, so_long->win, so_long->img.player,
			width, i * IMG_SIZE);
	else if (so_long->map.map[i][j] == 'E')
		mlx_put_image_to_window(so_long->mlx, so_long->win, so_long->img.exit_l,
			width, i * IMG_SIZE);
	else if (so_long->map.map[i][j] == 'C')
		mlx_put_image_to_window(so_long->mlx, so_long->win, so_long->img.coin1,
			width, i * IMG_SIZE);
}

int	render(t_so_long *so_long)
{
	int		i;
	size_t	j;
	int		width;

	if (so_long->win == NULL)
		return (0);
	i = 0;
	j = 0;
	width = 0;
	while (so_long->map.map[i])
	{
		while (so_long->map.map[i][j] && so_long->map.map[i][j] != '\n')
		{
			parse_chars(so_long, width, i, j);
			width += IMG_SIZE;
			j++;
		}
		j = 0;
		width = 0;
		i++;
	}
	return (1);
}

void	loop_images(t_so_long so_long)
{
	mlx_loop_hook(so_long.mlx, &render, &so_long);
	mlx_hook(so_long.win, 02, 1L << 0, &handle_keypress, &so_long);
	mlx_hook(so_long.win, 17, 0L,
		&handle_btnrealease, &so_long);
	mlx_loop(so_long.mlx);
}

void	destroy_images(t_so_long *so_long)
{
	mlx_destroy_image(so_long->mlx, so_long->img.wall);
	mlx_destroy_image(so_long->mlx, so_long->img.ground);
	mlx_destroy_image(so_long->mlx, so_long->img.player);
	mlx_destroy_image(so_long->mlx, so_long->img.exit_l);
	mlx_destroy_image(so_long->mlx, so_long->img.coin1);
}
