/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:05:14 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/23 16:15:33 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	*ft_pixel_texture_color(t_image image, int x, int y)
{
	
}

t_image	ft_init_texture(t_cub3d *cub3d, char *texture_name, void *image_ptr)
{
	image_ptr = mlx_xpm_file_to_image(cub3d->mlx, texture_name, &(cub3d->texture_n.width), &(cub3d->texture_n.height));
	cub3d->texture_e.ptr = mlx_xpm_file_to_image(cub3d->mlx, texture_name, &(cub3d->texture_n.width), &(cub3d->texture_n.height));
	cub3d->texture_w.ptr = mlx_xpm_file_to_image(cub3d->mlx, texture_name, &(cub3d->texture_n.width), &(cub3d->texture_n.height));
	cub3d->texture_s.ptr = mlx_xpm_file_to_image(cub3d->mlx, texture_name, &(cub3d->texture_n.width), &(cub3d->texture_n.height));
	cub3d->texture_n.
}