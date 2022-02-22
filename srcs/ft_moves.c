/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:36:34 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/22 10:48:22 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_if_can_move(t_cub3d *cub3d, int direction, char tile)
{
	double	x;
	double	y;
	
	x = cub3d->player.x;
	y = cub3d->player.y;
	if ((direction == DOWN
		&& cub3d->map.map[lround((y - (MOVE_SIZE * sin(cub3d->player_angle)))) / CUBE_SIZE][lround((x - MOVE_SIZE * cos(cub3d->player_angle))) / CUBE_SIZE] == tile)
		|| (direction == UP
		&& cub3d->map.map[lround((y + (MOVE_SIZE * sin(cub3d->player_angle)))) / CUBE_SIZE][lround((x + MOVE_SIZE * cos(cub3d->player_angle))) / CUBE_SIZE] == tile)
		)
		return (1);
	else
		return (0);
}

/*
** W = 13, A = 0, S = 1, D = 2, ESC = 53
*/

void	ft_move_player(t_cub3d *cub3d, int direction)
{
	if (check_if_can_move(cub3d, direction, '1') == 1)
		return ;
	if (direction == RIGHT)
		cub3d->player_angle += ANGLE_INC;
	else if (direction == LEFT)
		cub3d->player_angle -= ANGLE_INC;
	else if (direction == DOWN)
	{
		cub3d->player.x -= MOVE_SIZE * cos(cub3d->player_angle);
		cub3d->player.y -= MOVE_SIZE * sin(cub3d->player_angle);
	}
	else if (direction == UP)
	{
		cub3d->player.x += MOVE_SIZE * cos(cub3d->player_angle);
		cub3d->player.y += MOVE_SIZE * sin(cub3d->player_angle);
	}
	draw_image(cub3d, cub3d->map.map);
}