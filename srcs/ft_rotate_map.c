/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:18:35 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/21 17:26:48 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	**ft_malloc_rotated_map(char **map, t_cub3d *cub3d, int line_count)
{
	int		tab_size;
	int		i;
	int		j;
	char	**rotated_tab;

	i = -1;
	j = -1;
	while (map[++i])
	{
		while (map[i][++j])
			if (i == 1 || j > tab_size)
				tab_size = j;
		j = -1;
	}
	rotated_tab = malloc((++tab_size + 1) * sizeof(char *));
	if (!rotated_tab)
		ft_print_error(ERROR_MALLOC, cub3d);
	rotated_tab[tab_size] = NULL;
	while (--tab_size >= 0)
	{
		rotated_tab[tab_size] = ft_calloc(line_count + 1, sizeof(char));
		if (!rotated_tab[tab_size])
			ft_print_error(ERROR_MALLOC, cub3d);
	}
	return (rotated_tab);
}

char	**ft_rotate_map(char **map, t_cub3d *cub3d)
{
	int		i;
	int		j;
	char	**rotated_tab;

	rotated_tab = ft_malloc_rotated_map(map, cub3d, cub3d->map.line_count);
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			rotated_tab[j][i] = map[i][j];
		}
	}
	return (rotated_tab);
}
