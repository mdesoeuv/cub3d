/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:36:34 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/25 17:04:10 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_if_can_move(t_cub3d *cub3d, int direction, char tile)
{
	double	x;
	double	y;

	x = cub3d->player.x;
	y = cub3d->player.y;
	if ((direction == DOWN && \
		cub3d->map.map[lround((y - (MOVE_SIZE * \
		sin(cub3d->player_angle)))) / CUBE_SIZE][lround((x - \
		MOVE_SIZE * cos(cub3d->player_angle))) / CUBE_SIZE] == tile)
		|| (direction == UP && \
		cub3d->map.map[lround((y + (MOVE_SIZE * \
		sin(cub3d->player_angle)))) / CUBE_SIZE][lround((x + MOVE_SIZE * \
		cos(cub3d->player_angle))) / CUBE_SIZE] == tile)
		|| (direction == RIGHT && cub3d->map.map[lround((y + (MOVE_SIZE * \
		sin(cub3d->player_angle + M_PI / 2)))) / CUBE_SIZE][lround((x + \
		MOVE_SIZE * cos(cub3d->player_angle + M_PI / 2))) / CUBE_SIZE] == tile)
		|| (direction == LEFT && cub3d->map.map[lround((y + (MOVE_SIZE * \
		sin(cub3d->player_angle - M_PI / 2)))) / CUBE_SIZE][lround((x + \
		MOVE_SIZE * cos(cub3d->player_angle - M_PI / 2))) / CUBE_SIZE] == tile))
		return (1);
	else
		return (0);
}

void	ft_get_move(t_cub3d *cub3d, int direction)
{
	if (direction == DOWN)
	{
		cub3d->player.x -= (int)(MOVE_SIZE * cos(cub3d->player_angle));
		cub3d->player.y -= (int)(MOVE_SIZE * sin(cub3d->player_angle));
	}
	else if (direction == UP)
	{
		cub3d->player.x += (int)(MOVE_SIZE * cos(cub3d->player_angle));
		cub3d->player.y += (int)(MOVE_SIZE * sin(cub3d->player_angle));
	}
	else if (direction == LEFT)
	{
		cub3d->player.x += (int)(MOVE_SIZE \
			* cos(cub3d->player_angle - M_PI / 2));
		cub3d->player.y += (int)(MOVE_SIZE \
			* sin(cub3d->player_angle - M_PI / 2));
	}
	else if (direction == RIGHT)
	{
		cub3d->player.x += (int)(MOVE_SIZE \
			* cos(cub3d->player_angle + M_PI / 2));
		cub3d->player.y += (int)(MOVE_SIZE \
			* sin(cub3d->player_angle + M_PI / 2));
	}
}

void	ft_move_player(t_cub3d *cub3d, int direction)
{
	if (check_if_can_move(cub3d, direction, '1') == 1)
		return ;
	if (direction == ROT_RIGHT)
	{
		cub3d->player_angle += ANGLE_INC;
		if (cub3d->player_angle > M_PI * 2)
			cub3d->player_angle -= M_PI * 2;
	}
	else if (direction == ROT_LEFT)
	{
		cub3d->player_angle -= ANGLE_INC;
		if (cub3d->player_angle < 0)
			cub3d->player_angle += M_PI * 2;
	}
	else if (direction == DOWN)
		ft_get_move(cub3d, DOWN);
	else if (direction == UP)
		ft_get_move(cub3d, UP);
	else if (direction == LEFT)
		ft_get_move(cub3d, LEFT);
	else if (direction == RIGHT)
		ft_get_move(cub3d, RIGHT);
	draw_image_3d(cub3d);
}
