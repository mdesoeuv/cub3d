/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_window_images.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 11:59:47 by vchevill          #+#    #+#             */
/*   Updated: 2022/01/20 14:16:33 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_init_window(t_so_long *so_long)
{
	so_long->mlx = mlx_init();
	if (!so_long->mlx)
		ft_print_error(ERROR_MINILIBX, so_long);
	so_long->win = mlx_new_window(so_long->mlx, so_long->win_width,
			so_long->win_height, "So long");
	if (!so_long->win)
	{
		free(so_long->win);
		ft_print_error(ERROR_MINILIBX, so_long);
	}
}

void	ft_init_images(t_so_long *so_long)
{
	so_long->img.ground = mlx_xpm_file_to_image(so_long->mlx, GROUND,
			&so_long->img.width, &so_long->img.height);
	so_long->img.exit_l = mlx_xpm_file_to_image(so_long->mlx, LOCKED,
			&so_long->img.width, &so_long->img.height);
	so_long->img.player = mlx_xpm_file_to_image(so_long->mlx, PLAYER,
			&so_long->img.width, &so_long->img.height);
	so_long->img.wall = mlx_xpm_file_to_image(so_long->mlx, W_RAND,
			&so_long->img.width, &so_long->img.height);
	so_long->img.coin1 = mlx_xpm_file_to_image(so_long->mlx, COIN1,
			&so_long->img.width, &so_long->img.height);
}
