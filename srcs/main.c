/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 09:52:46 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/25 17:26:19 by vchevill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/get_next_line.h"

void	display_map_and_textures(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	/*dprintf(1, "texture NO=%s=\n", cub3d->texture_n.);
	dprintf(1, "texture S=%s=\n", cub3d->texture_s);
	dprintf(1, "texture EAST=%s=\n", cub3d->texture_e);
	dprintf(1, "texture WEST=%s=\n", cub3d->texture_w);*/
	dprintf(1, "color ground=%i,%i,%i=\n", cub3d->color_ground[0],cub3d->color_ground[1],cub3d->color_ground[2]);
	dprintf(1, "color ceiling=%i,%i,%i=\n", cub3d->color_ceiling[0],cub3d->color_ceiling[1],cub3d->color_ceiling[2]);
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
		ft_init_vars(&cub3d);
		ft_check_file_extension(argv[1], &cub3d);
		cub3d.mlx = mlx_init();
		if (!cub3d.mlx)
			ft_print_error(ERROR_MINILIBX, &cub3d);
		ft_create_map(argv[1], &cub3d);
		ft_check_map(&cub3d);
		ft_init_window(&cub3d);
		display_map_and_textures(&cub3d);
		ft_init_render_image(&cub3d);
		ft_rendering(&cub3d);
	}
	else
		ft_putstr_fd("Error\n", 2);
	return (0);
}
