/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:36:34 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/28 15:03:01 by vchevill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	step_move_check(t_cub3d *cub3d, int direction, int step_move, double angle)
{
	double	x;
	double	y;

	x = cub3d->player.x;
	y = cub3d->player.y;
	if ((direction == DOWN && \
	cub3d->map.map[lround((y - (step_move * \
	sin(angle)))) / CUBE_SIZE][lround((x - \
	step_move * cos(angle))) / CUBE_SIZE] == '1')
	|| (direction == UP && \
	cub3d->map.map[lround((y + (step_move * \
	sin(angle)))) / CUBE_SIZE][lround((x + step_move * \
	cos(angle))) / CUBE_SIZE] == '1')
	|| (direction == RIGHT && cub3d->map.map[lround((y + (step_move * \
	sin(angle + M_PI / 2)))) / CUBE_SIZE][lround((x + \
	step_move * cos(angle + M_PI / 2))) / CUBE_SIZE] == '1')
	|| (direction == LEFT && cub3d->map.map[lround((y + (step_move * \
	sin(angle - M_PI / 2)))) / CUBE_SIZE][lround((x + \
	step_move * cos(angle - M_PI / 2))) / CUBE_SIZE] == '1'))
		return (1);
	else
		return (0);
}

static int	check_if_can_move(t_cub3d *cub3d, int direction, char tile)
{
	int		step_move;
	int		i;
	double	angle;

	tile = '1';
	angle = cub3d->player_angle - (3 * (cub3d->fov / WINDOW_WIDTH));
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	else if (angle < 0)
		angle += 2 * M_PI;
	step_move = 1;
	i = 0;
	while (i < 7)
	{
		while (step_move < MOVE_SIZE)
		{
			if (step_move_check(cub3d, direction, step_move, angle) == 1)
				return (1);
			step_move++;
		}
		ft_increment_ray_absolute_angle(cub3d, angle);
		i++;
	}
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
		cub3d->player_angle += M_PI / ANGLE_INC;
		if (cub3d->player_angle > M_PI * 2)
			cub3d->player_angle -= M_PI * 2;
	}
	else if (direction == ROT_LEFT)
	{
		cub3d->player_angle -= M_PI / ANGLE_INC;
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
