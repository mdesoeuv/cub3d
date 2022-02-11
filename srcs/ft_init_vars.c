/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:40:01 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/11 13:44:40 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
// recuperer les parametres

void	ft_init_vars(t_cub3d *cub3d)
{
	cub3d->texture_e = NULL;
	cub3d->texture_s = NULL;
	cub3d->texture_n = NULL;
	cub3d->texture_w = NULL;
	cub3d->texture_ceiling = NULL;
	cub3d->texture_ground = NULL;

	
	cub3d->x = 0;
	cub3d->y = 0;
	cub3d->win_height = cub3d->map.line_count * IMG_SIZE;
	cub3d->win_width = (ft_strlen(cub3d->map.map[0]) - 1) * IMG_SIZE;
	cub3d->img.height = IMG_SIZE;
	cub3d->img.width = IMG_SIZE;
}
