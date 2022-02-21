/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:42:35 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/21 11:32:08 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
/*
static void	ft_check_top_and_bottom_edges(int row, t_so_long *so_long)
{
	int	i;

	i = 0;
	while (so_long->map.map[row][i] && so_long->map.map[row][i] != '\n')
	{
		if (so_long->map.map[row][i] != '1')
			ft_print_error(ERROR_EDGES, so_long);
		i++;
	}
}
*/
static void	ft_check_left_and_right_edges(t_cub3d *cub3d)
{
	int	i;
	int	j;
	int	d;

	i = -1;
	while (++i < cub3d->map.line_count - 1)
	{
		j = -1;
		d = ft_strlen(cub3d->map.map[i]);
		while (cub3d->map.map[i][++j])
			if (cub3d->map.map[i][j] == '1')
				break ;
		while (d > 0)
			if (cub3d->map.map[i][--d] == '1')
				break ;
		if (!cub3d->map.map[i][j] || d == j)
			ft_print_error(ERROR_EDGES, cub3d);
		i++;
	}
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
	//ft_check_top_and_bottom_edges(cub3d);
	ft_check_left_and_right_edges(cub3d);
}
