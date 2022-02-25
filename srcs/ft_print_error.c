/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:03:16 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/25 16:28:14 by vchevill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_print_error(char *str, t_cub3d *cub3d)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	if (cub3d->texture_s.ptr)
		free(cub3d->texture_s.ptr);
	if (cub3d->texture_n.ptr)
		free(cub3d->texture_n.ptr);
	if (cub3d->texture_w.ptr)
		free(cub3d->texture_w.ptr);
	if (cub3d->texture_e.ptr)
		free(cub3d->texture_e.ptr); // free data ?
	if (cub3d->map.map)
		ft_free_split(cub3d->map.map);
	exit(1);
}
