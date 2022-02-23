/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_textures_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 14:24:55 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/23 16:34:59 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_all_textures_declared(t_cub3d *cub3d)
{
	if (cub3d->texture_e.ptr && cub3d->texture_w.ptr
		&& cub3d->texture_n.ptr && cub3d->texture_s.ptr
		&& cub3d->color_ceiling[0] != -1 && cub3d->color_ground[0] != -1)
		return (1);
	else
		return (0);
}

void	get_textures_path(t_cub3d *cub3d)
{
	char	*line;

	cub3d->map.line_start_map_in_cub = 0;
	line = get_next_line(cub3d->map.fd);
	cub3d->map.line_start_map_in_cub++;
	while (line && !ft_all_textures_declared(cub3d))
	{
		ft_define_texture(cub3d, line);
		free(line);
		line = get_next_line(cub3d->map.fd);
		cub3d->map.line_start_map_in_cub++;
		if (line == NULL)
		{
			close(cub3d->map.fd);
			ft_print_error(ERROR_MALLOC, cub3d);
		}
	}
	free(line);
}
