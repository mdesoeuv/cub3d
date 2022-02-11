/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:40:01 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/11 12:26:24 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_init_map(t_so_long *cub3d)
{
	cub3d->x = 0;
	cub3d->y = 0;
	cub3d->win_height = cub3d->map.line_count * IMG_SIZE;
	cub3d->win_width = (ft_strlen(cub3d->map.map[0]) - 1) * IMG_SIZE;
	cub3d->img.height = IMG_SIZE;
	cub3d->img.width = IMG_SIZE;
}
