/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:03:16 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/25 17:34:18 by vchevill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_free_image(void *mlx_ptr, t_image *image)
{
	mlx_destroy_image(mlx_ptr, image->ptr);
}

void	ft_free(t_cub3d *cub3d)
{
	if (cub3d->texture_s.ptr)
		ft_free_image(cub3d->mlx, &(cub3d->texture_s));
	if (cub3d->texture_n.ptr)
		ft_free_image(cub3d->mlx, &(cub3d->texture_n));
	if (cub3d->texture_w.ptr)
		ft_free_image(cub3d->mlx, &(cub3d->texture_w));
	if (cub3d->texture_e.ptr)
		ft_free_image(cub3d->mlx, &(cub3d->texture_e));
	if (cub3d->render_3d.ptr)
		ft_free_image(cub3d->mlx, &(cub3d->render_3d));
	if (cub3d->map.map)
		ft_free_split(cub3d->map.map);
	if (cub3d->window_ptr)
		mlx_destroy_window(cub3d->mlx, cub3d->window_ptr);
	exit(0);
}

void	ft_print_error(char *str, t_cub3d *cub3d)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	ft_free(cub3d);
}
