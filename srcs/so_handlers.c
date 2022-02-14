/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:13:53 by vchevill          #+#    #+#             */
/*   Updated: 2022/01/20 15:14:03 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	handle_resize(t_so_long *so_long)
{
	render(so_long);
	return (0);
}

int	handle_keypress(int keysym, t_so_long *so_long)
{
	if (keysym == 53)
	{
		destroy_images(so_long);
		mlx_destroy_window(so_long->mlx, so_long->win);
		so_long->win = NULL;
		if (so_long->map.map)
			ft_free(so_long->map.map);
		exit(0);
	}
	else if (keysym == 0 || keysym == 1 || keysym == 2 || keysym == 13)
		ft_move_player(so_long, keysym);
	return (0);
}

int	handle_btnrealease(t_so_long *so_long)
{
	destroy_images(so_long);
	mlx_destroy_window(so_long->mlx, so_long->win);
	so_long->win = NULL;
	if (so_long->map.map)
		ft_free(so_long->map.map);
	exit(0);
	return (0);
}
