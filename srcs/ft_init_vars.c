/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:40:01 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/25 17:32:53 by vchevill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_init_vars(t_cub3d *cub3d)
{
	cub3d->texture_e.ptr = NULL;
	cub3d->texture_s.ptr = NULL;
	cub3d->texture_n.ptr = NULL;
	cub3d->texture_w.ptr = NULL;
	cub3d->window_ptr = NULL;
	cub3d->render_3d.ptr = NULL;
	cub3d->map.map = NULL;
	cub3d->color_ceiling[0] = -1;
	cub3d->color_ground[0] = -1;
	cub3d->map.longest_line = 0;
	cub3d->win_height = WINDOW_HEIGHT;
	cub3d->win_width = WINDOW_WIDTH;
	cub3d->fov = (FOV * (M_PI / 180));
	cub3d->player_dist = (WINDOW_WIDTH / 2) / tan(cub3d->fov / 2);
	cub3d->slice_ratio = CUBE_SIZE * cub3d->player_dist;
}
