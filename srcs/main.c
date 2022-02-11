/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 09:52:46 by vchevill          #+#    #+#             */
/*   Updated: 2022/01/20 15:14:39 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../includes/get_next_line.h"

int	main(int argc, char **argv)
{
	t_so_long	so_long;

	if (argc == 2)
	{
		ft_check_file_extension(argv[1], &so_long);
		ft_create_map(argv[1], &so_long);
		ft_init_map(&so_long);
		ft_check_map(&so_long);
		ft_init_window(&so_long);
		ft_init_images(&so_long);
		render(&so_long);
		loop_images(so_long);
		destroy_images(&so_long);
		mlx_destroy_window(so_long.mlx, so_long.win);
		so_long.win = NULL;
		if (so_long.map.map)
			ft_free(so_long.map.map);
	}
	else
		ft_print_error(ERROR_FILENAME_MISSING, &so_long);
}
