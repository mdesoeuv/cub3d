/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:36:34 by vchevill          #+#    #+#             */
/*   Updated: 2022/01/20 15:13:15 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	move_msg(t_so_long *so_long)
{
	printf("Moves counter : %d\n", so_long->steps_count);
}

static int	check_if_can_move(t_so_long *so_long, int direction, char tile)
{
	if ((direction == 2
			&& so_long->map.map[so_long->player_y][so_long->player_x + 1]
		== tile)
		|| (direction == 0
		&& so_long->map.map[so_long->player_y][so_long->player_x - 1] == tile)
		|| (direction == 1
		&& so_long->map.map[so_long->player_y + 1][so_long->player_x] == tile)
		|| (direction == 13
		&& so_long->map.map[so_long->player_y - 1][so_long->player_x] == tile)
		)
		return (1);
	else
		return (0);
}

static void	collect_coins(t_so_long *so_long, int direction)
{
	if ((direction == 2
			&& so_long->map.map[so_long->player_y][so_long->player_x + 1]
		== 'C')
		|| (direction == 0
		&& so_long->map.map[so_long->player_y][so_long->player_x - 1] == 'C')
		|| (direction == 1
		&& so_long->map.map[so_long->player_y + 1][so_long->player_x] == 'C')
		|| (direction == 13
		&& so_long->map.map[so_long->player_y - 1][so_long->player_x] == 'C'))
		so_long->map.collected++;
}

static void	win_game(t_so_long *so_long)
{
	if (so_long->map.can_exit == 1)
	{
		destroy_images(so_long);
		mlx_destroy_window(so_long->mlx, so_long->win);
		so_long->win = NULL;
		printf("You WON ! Congratulations !\n");
		if (so_long->map.map)
			ft_free(so_long->map.map);
		exit(0);
	}
}

void	ft_move_player(t_so_long *so_long, int direction)
{
	if (check_if_can_move(so_long, direction, '1') == 1
		|| (so_long->map.can_exit == 0
			&& check_if_can_move(so_long, direction, 'E') == 1))
		return ;
	so_long->steps_count++;
	collect_coins(so_long, direction);
	if (so_long->map.collected == so_long->map.count_c)
		so_long->map.can_exit = 1;
	so_long->map.map[so_long->player_y][so_long->player_x] = '0';
	if (direction == 2)
		so_long->player_x++;
	else if (direction == 0)
		so_long->player_x--;
	else if (direction == 1)
		so_long->player_y++;
	else if (direction == 13)
		so_long->player_y--;
	move_msg(so_long);
	if (so_long->map.can_exit == 1
		&& so_long->map.map[so_long->player_y][so_long->player_x] == 'E')
		win_game(so_long);
	so_long->map.map[so_long->player_y][so_long->player_x] = 'P';
}
