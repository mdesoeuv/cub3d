/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_window_images.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 11:59:47 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/22 14:22:33 by vchevill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_init_window(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init();
	if (!cub3d->mlx)
		ft_print_error(ERROR_MINILIBX, cub3d);
	cub3d->window_ptr = mlx_new_window(cub3d->mlx, cub3d->win_width,
			cub3d->win_height, "cub3d");
	if (!cub3d->window_ptr)
		ft_print_error(ERROR_MINILIBX, cub3d);
}

void	ft_init_render_image(t_cub3d *cub3d)
{
	cub3d->win_render.pointer = mlx_new_image(cub3d->mlx, cub3d->win_width, \
		cub3d->win_height);
	cub3d->win_render.data = mlx_get_data_addr(cub3d->win_render.pointer, \
		&(cub3d->win_render.bits_per_pixel), &(cub3d->win_render.line_size), \
		&(cub3d->win_render.endian));
}
