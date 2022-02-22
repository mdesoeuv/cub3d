/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:13:53 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/22 11:50:25 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_keypress(int keysym, t_cub3d *cub3d)
{
	if (keysym == 53)
	{
		// destroy_images(cub3d);
		mlx_destroy_window(cub3d->mlx, cub3d->window_ptr);
		cub3d->window_ptr = NULL;
		// if (cub3d->map.map)
		// 	ft_free(cub3d->map.map);
		exit(0);
	}
	else if (keysym == 0 || keysym == 1 || keysym == 2 || keysym == 13)
		ft_move_player(cub3d, keysym);
	return (0);
}

int	handle_btnrealease(t_cub3d *cub3d)
{
	// destroy_images(cub3d);
	mlx_destroy_window(cub3d->mlx, cub3d->window_ptr);
	cub3d->window_ptr = NULL;
	// if (cub3d->map.map)
	// 	ft_free(cub3d->map.map);
	exit(0);
	return (0);
}
