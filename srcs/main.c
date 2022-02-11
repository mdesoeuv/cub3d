/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 09:52:46 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/11 13:39:28 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../includes/get_next_line.h"

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	if (argc == 2)
	{
		ft_check_file_extension(argv[1], &cub3d);
		ft_init_vars(&cub3d);
		ft_create_map(argv[1], &cub3d);
		ft_check_map(&cub3d);
		ft_init_window(&cub3d);
		ft_init_images(&cub3d);
		render(&cub3d);
		loop_images(cub3d);
		destroy_images(&cub3d);
		mlx_destroy_window(cub3d.mlx, cub3d.win);
		cub3d.win = NULL;
		if (cub3d.map.map)
			ft_free(cub3d.map.map);
	}
	else
		ft_print_error(ERROR_FILENAME_MISSING, &cub3d);
}
