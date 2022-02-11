/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file_extension.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 09:57:45 by vchevill          #+#    #+#             */
/*   Updated: 2022/01/20 14:12:33 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_check_file_extension(char *path, t_so_long *so_long)
{
	size_t	len;

	len = ft_strlen(path);
	so_long->map.fd = open(path, O_RDONLY);
	close(so_long->map.fd);
	if (so_long->map.fd < 0)
		ft_print_error(ERROR_FILE_OPENING, so_long);
	else if ((path[len - 3] != 'b' && path[len - 2] != 'e'
			&& path[len - 1] != 'r'
			&& path[len - 4] != '.'))
		ft_print_error(ERROR_FILE_EXTENSION_NAME, so_long);
}
