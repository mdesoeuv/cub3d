/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:05:14 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/23 16:30:51 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	*ft_pixel_texture_color(t_image image, int x, int y)
{
	
}

void	ft_init_texture(t_cub3d *cub3d, char *texture_name, t_image *image_struc)
{
	image_struc->ptr = mlx_xpm_file_to_image(cub3d->mlx, texture_name, &(cub3d->texture_n.width), &(cub3d->texture_n.height));
	if(!image_struc->ptr)
		ft_print_error(ERROR_XPM_INIT, cub3d);
	image_struc->data = mlx_get_data_addr(image_struc->ptr, \
		&(image_struc->bits_per_pixel), &(image_struc->line_size), \
		&(image_struc->endian));
}