/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_moves.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:36:34 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/21 17:47:04 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_if_can_move(t_cub3d *cub3d, int direction, char tile)
{
	if ((direction == 2
			&& cub3d->map.map[cub3d->player.y / CUBE_SIZE][(cub3d->player.x + MOVE_SIZE) / CUBE_SIZE]
		== tile)
		|| (direction == 0
		&& cub3d->map.map[cub3d->player.y / CUBE_SIZE][(cub3d->player.x - MOVE_SIZE) / CUBE_SIZE] == tile)
		|| (direction == 1
		&& cub3d->map.map[(cub3d->player.y + MOVE_SIZE) / CUBE_SIZE][cub3d->player.x / CUBE_SIZE] == tile)
		|| (direction == 13
		&& cub3d->map.map[(cub3d->player.y - MOVE_SIZE) / CUBE_SIZE][cub3d->player.x / CUBE_SIZE] == tile)
		)
		return (1);
	else
		return (0);
}

void	ft_move_player(t_cub3d *cub3d, int direction)
{
	if (check_if_can_move(cub3d, direction, '1') == 1)
		return ;
	if (direction == 2)
		cub3d->player.x += MOVE_SIZE;
	else if (direction == 0)
		cub3d->player.x -= MOVE_SIZE;
	else if (direction == 1)
		cub3d->player.y += MOVE_SIZE;
	else if (direction == 13)
		cub3d->player.y -= MOVE_SIZE;
	draw_map(cub3d, cub3d->map.map);
	draw_player(cub3d);
}