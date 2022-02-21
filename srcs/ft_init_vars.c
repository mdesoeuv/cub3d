/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:40:01 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/21 17:58:46 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_init_vars(t_cub3d *cub3d)
{
	cub3d->texture_e = NULL;
	cub3d->texture_s = NULL;
	cub3d->texture_n = NULL;
	cub3d->texture_w = NULL;
	cub3d->color_ceiling = NULL;
	cub3d->color_ground = NULL;
}
