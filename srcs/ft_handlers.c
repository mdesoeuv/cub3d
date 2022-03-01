/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:13:53 by vchevill          #+#    #+#             */
/*   Updated: 2022/03/01 11:46:07 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_keypress(int keysym, t_cub3d *cub3d)
{
	if (keysym == 53)
	{
		mlx_destroy_window(cub3d->mlx, cub3d->window_ptr);
		cub3d->window_ptr = NULL;
		exit(0);
	}
	else if (keysym == 0 || keysym == 1 || keysym == 2 || keysym == 13
		|| keysym == 123 || keysym == 124 || keysym == 125 || keysym == 126)
		ft_move_player(cub3d, keysym);
	return (0);
}

int	handle_btnrealease(t_cub3d *cub3d)
{
	mlx_destroy_window(cub3d->mlx, cub3d->window_ptr);
	cub3d->window_ptr = NULL;
	exit(0);
	return (0);
}
