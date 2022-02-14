/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 09:52:46 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/14 14:40:06 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/get_next_line.h"

void	display_map_and_textures(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	dprintf(1, "texture NO=%s=\n", cub3d->texture_n);
	dprintf(1, "texture S=%s=\n", cub3d->texture_s);
	dprintf(1, "texture EAST=%s=\n", cub3d->texture_e);
	dprintf(1, "texture WEST=%s=\n", cub3d->texture_w);
	dprintf(1, "color ground=%s=\n", cub3d->color_ground);
	dprintf(1, "color ceilling=%s=\n", cub3d->color_ceiling);
	while (cub3d->map.map[i])
	{
		dprintf(1, "%s\n", cub3d->map.map[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	cub3d.map.map = NULL;
	if (argc == 2)
	{
		ft_check_file_extension(argv[1], &cub3d);
		ft_init_vars(&cub3d);
		ft_create_map(argv[1], &cub3d);
		display_map_and_textures(&cub3d);
		ft_print_error(ERROR_FILENAME_MISSING, &cub3d);
		exit(0);
		ft_check_map(&cub3d);
	/*	ft_init_window(&cub3d);
		ft_init_images(&cub3d);
		render(&cub3d);
		loop_images(cub3d);
		destroy_images(&cub3d);
		mlx_destroy_window(cub3d.mlx, cub3d.win);
		cub3d.win = NULL;
		if (cub3d.map.map)
			ft_free_split(cub3d.map.map);*/
	}
	else
		ft_print_error(ERROR_FILENAME_MISSING, &cub3d);
}
