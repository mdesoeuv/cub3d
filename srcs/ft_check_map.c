/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:42:35 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/21 16:25:21 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ft_check_line_edges(char **map, t_cub3d *cub3d)
{
	int	i;
	int	j;
	int	first;

	i = -1;
	while (map[++i])
	{
		j = -1;
		first = -1;
		while (map[i][++j])
		{
			if (map[i][j] == ' ')
			{
				if (j > 0 && map[i][j - 1] == '0')
					ft_print_error(ERROR_EDGES, cub3d);
				while (map[i][j] == ' ')
					if (!map[i][++j])
						ft_print_error(ERROR_EDGES, cub3d);
				if (map[i][j] == '0')
					ft_print_error(ERROR_EDGES, cub3d);
				first = j;
			}
			else if (map[i][j] == '0' && first == -1)
				ft_print_error(ERROR_EDGES, cub3d);
			else if (!map[i][j + 1] && map[i][j] == '0')
				ft_print_error(ERROR_EDGES, cub3d);
			else if (map[i][j] == '1')
				first = j;
		}
		if (first == -1)
			ft_print_error(ERROR_EDGES, cub3d);
	}
}

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

static void	ft_get_start_direction(t_cub3d *cub3d)
{
	int		i;
	int		j;
	int		count_direction;

	i = 0;
	j = 0;
	count_direction = 0;
	while (cub3d->map.map[i])
	{	
		while (j < ft_strlen(cub3d->map.map[i]) - 1)
		{
			if (ft_strchr("NSEW", cub3d->map.map[i][j]))
			{
				cub3d->map.direction = cub3d->map.map[i][j];
				count_direction++;
			}	
			j++;
		}
		j = 0;
		i++;
	}
	if (!count_direction)
		ft_print_error(ERROR_MISSING_PLAYER, cub3d);
	if (count_direction > 1)
		ft_print_error(ERROR_TOO_MANY_PLAYERS, cub3d);
}

void	ft_check_map(t_cub3d *cub3d)
{
	int		i;
	int		j;
	char	**rotated_map;

	i = 0;
	j = 0;
	while (cub3d->map.map[i])
	{	
		while (j < ft_strlen(cub3d->map.map[i]) - 1)
		{
			if (!ft_strchr("01NSEW ", cub3d->map.map[i][j]))
				ft_print_error(ERROR_OTHER_CHARS, cub3d);
			j++;
		}
		j = 0;
		i++;
	}
	ft_get_start_direction(cub3d);
	ft_check_line_edges(cub3d->map.map, cub3d);
	rotated_map = ft_rotate_map(cub3d->map.map, cub3d);
	ft_check_line_edges(rotated_map, cub3d);
	ft_free_split(rotated_map);
}
