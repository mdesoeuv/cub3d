/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:36:34 by vchevill          #+#    #+#             */
/*   Updated: 2022/03/01 11:21:58 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	angle_normalize(double angle)
{
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	else if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

int	step_move_check(t_cub3d *cub3d, int direction, int step_move, double angle)
{
	double	x;
	double	y;

	angle = angle_normalize(angle);
	x = cub3d->player.x;
	y = cub3d->player.y;
	if ((direction == DOWN && \
	cub3d->map.map[lround((y - (step_move * \
	sin(angle)))) / CUB_SIZE][lround((x - \
	step_move * cos(angle))) / CUB_SIZE] == '1')
	|| (direction == UP && \
	cub3d->map.map[lround((y + (step_move * \
	sin(angle)))) / CUB_SIZE][lround((x + step_move * \
	cos(angle))) / CUB_SIZE] == '1')
	|| (direction == RIGHT && cub3d->map.map[lround((y + (step_move * \
	sin(angle + M_PI / 2)))) / CUB_SIZE][lround((x + \
	step_move * cos(angle + M_PI / 2))) / CUB_SIZE] == '1')
	|| (direction == LEFT && cub3d->map.map[lround((y + (step_move * \
	sin(angle - M_PI / 2)))) / CUB_SIZE][lround((x + \
	step_move * cos(angle - M_PI / 2))) / CUB_SIZE] == '1'))
		return (1);
	else
		return (0);
}

static int	check_if_can_move(t_cub3d *cub3d, int direction)
{
	int		step_move;
	int		i;

	step_move = 1;
	while (step_move < MOVE_SIZE)
	{
		i = 2;
		while (i >= 0)
		{
			if (step_move_check(cub3d, direction, \
				step_move, cub3d->player_angle - (0.05 * i)) == 1)
				return (1);
			if (step_move_check(cub3d, direction, \
				step_move, cub3d->player_angle + (0.05 * i)) == 1)
				return (1);
			i--;
		}
		step_move++;
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
	if (check_if_can_move(cub3d, direction) == 1)
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
	ft_draw_image(cub3d);
}
