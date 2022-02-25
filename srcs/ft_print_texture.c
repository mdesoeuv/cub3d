/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:05:14 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/25 16:04:30 by vchevill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_pixel_texture_color(t_cub3d *cub3d, t_image image, int x, int y)
{
	cub3d->color_texture[2] = image.data[y * image.line_size + \
		x * image.bits_per_pixel / 8];
	cub3d->color_texture[1] = image.data[(y * image.line_size + \
		x * image.bits_per_pixel / 8) + 1];
	cub3d->color_texture[0] = image.data[(y * image.line_size + \
		x * image.bits_per_pixel / 8) + 2];
}

void	ft_init_texture(t_cub3d *cub3d, char *texture_path, t_image *image_struc)
{
	dprintf(1, "%s\n",texture_path);
	image_struc->ptr = mlx_xpm_file_to_image(cub3d->mlx, texture_path, &(image_struc->width), &(image_struc->height));
	if(!image_struc->ptr)
		ft_print_error(ERROR_XPM_INIT, cub3d);
	image_struc->data = mlx_get_data_addr(image_struc->ptr, \
		&(image_struc->bits_per_pixel), &(image_struc->line_size), \
		&(image_struc->endian));
}