/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 09:52:46 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/28 15:32:46 by vchevill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/get_next_line.h"

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	cub3d.map.map = NULL;
	if (argc == 2)
	{
		ft_init_vars(&cub3d);
		ft_check_file_extension(argv[1], &cub3d);
		cub3d.mlx = mlx_init();
		if (!cub3d.mlx)
			ft_print_error(ERROR_MINILIBX, &cub3d);
		ft_create_map(argv[1], &cub3d);
		ft_check_map(&cub3d);
		ft_init_window(&cub3d);
		ft_init_render_image(&cub3d);
		ft_rendering(&cub3d);
	}
	else
		ft_putstr_fd("Error\n", 2);
	return (0);
}
