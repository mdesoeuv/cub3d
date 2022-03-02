/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:13:53 by vchevill          #+#    #+#             */
/*   Updated: 2022/03/02 08:43:44 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_keypress(int keysym, t_cub3d *cub3d)
{
	if (keysym == DOWN_BIS)
		keysym = DOWN;
	if (keysym == UP_BIS)
		keysym = UP;
	if (keysym == 53)
	{
		ft_free(cub3d);
		exit(0);
	}
	else if (keysym == 0 || keysym == 1 || keysym == 2 || keysym == 13
		|| keysym == 123 || keysym == 124)
		ft_move_player(cub3d, keysym);
	return (0);
}

int	handle_btnrealease(t_cub3d *cub3d)
{
	ft_free(cub3d);
	return (0);
}
