/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file_extension.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 09:57:45 by vchevill          #+#    #+#             */
/*   Updated: 2022/03/03 13:51:20 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_check_file_extension(char *path, t_cub3d *cub3d)
{
	size_t	len;

	len = ft_strlen(path);
	cub3d->map.fd = open(path, O_RDONLY);
	if (cub3d->map.fd < 0)
		ft_print_error(ERROR_FILE_OPENING, cub3d);
	else if ((path[len - 3] != 'c' || path[len - 2] != 'u'
			|| path[len - 1] != 'b'
			|| path[len - 4] != '.'))
		ft_print_error(ERROR_FILE_EXTENSION_NAME, cub3d);
	close(cub3d->map.fd);
}
