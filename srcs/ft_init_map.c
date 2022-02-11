/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:40:01 by vchevill          #+#    #+#             */
/*   Updated: 2022/01/20 14:16:29 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_init_map(t_so_long *so_long)
{
	so_long->x = 0;
	so_long->y = 0;
	so_long->map.count_p = 0;
	so_long->map.count_e = 0;
	so_long->map.count_c = 0;
	so_long->map.collected = 0;
	so_long->map.can_exit = 0;
	so_long->steps_count = 0;
	so_long->win_height = so_long->map.line_count * IMG_SIZE;
	so_long->win_width = (ft_strlen(so_long->map.map[0]) - 1) * IMG_SIZE;
	so_long->img.height = IMG_SIZE;
	so_long->img.width = IMG_SIZE;
}
