/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:40:01 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/21 17:53:38 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
// recuperer les parametres

void	ft_init_vars(t_cub3d *cub3d)
{
	cub3d->texture_e = NULL;
	cub3d->texture_s = NULL;
	cub3d->texture_n = NULL;
	cub3d->texture_w = NULL;
	cub3d->color_ceiling = NULL;
	cub3d->color_ground = NULL;
	cub3d->win_height = cub3d->map.line_count * CUBE_SIZE;
	cub3d->win_width = (ft_strlen(cub3d->map.map[0]) - 1) * CUBE_SIZE;
	cub3d->player.x = 5 * CUBE_SIZE;
	cub3d->player.y = 6 * CUBE_SIZE;
}
