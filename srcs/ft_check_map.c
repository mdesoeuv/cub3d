/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:42:35 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/28 15:30:19 by vchevill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int
	ft_check_spaces_in_line(char **map, t_cub3d *cub3d, int first, int i)
{
	int	j;

	j = -1;
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
	return (first);
}

static void	ft_check_line_edges(char **map, t_cub3d *cub3d)
{
	int	i;
	int	first;

	i = -1;
	while (map[++i])
	{
		first = -1;
		first = ft_check_spaces_in_line(map, cub3d, first, i);
		if (first == -1)
			ft_print_error(ERROR_EDGES, cub3d);
	}
}

static void	ft_init_player_angle(t_cub3d *cub3d, int count_direction)
{
	if (!count_direction)
		ft_print_error(ERROR_MISSING_PLAYER, cub3d);
	if (count_direction > 1)
		ft_print_error(ERROR_TOO_MANY_PLAYERS, cub3d);
	if (cub3d->map.map[start_y][start_x] == 'E')
		cub3d->player_angle = 2 * M_PI;
	else if (cub3d->map.map[start_y][start_x] == 'S')
		cub3d->player_angle = M_PI / 2;
	else if (cub3d->map.map[start_y][start_x] == 'W')
		cub3d->player_angle = M_PI;
	else if (cub3d->map.map[start_y][start_x] == 'N')
		cub3d->player_angle = 3 * M_PI / 2;
}

static int	ft_get_start_direction(t_cub3d *cub3d)
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
				cub3d->player.x = j * CUBE_SIZE + CUBE_SIZE / 2;
				cub3d->player.y = i * CUBE_SIZE + CUBE_SIZE / 2;
			}	
			j++;
		}
		j = 0;
		i++;
	}
	ft_init_player_angle(cub3d, count_direction);
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
