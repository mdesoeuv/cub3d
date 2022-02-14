/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:03:16 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/14 11:18:50 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void	ft_print_error(char *str, t_cub3d *cub3d)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	if (cub3d->map.map)
		ft_free_split(cub3d->map.map);
	exit(1);
}
