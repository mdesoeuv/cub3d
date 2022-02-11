/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:42:35 by vchevill          #+#    #+#             */
/*   Updated: 2022/01/20 14:29:13 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	ft_check_top_and_bottom(int row, t_so_long *so_long)
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

static void	ft_check_edges(t_so_long *so_long)
{
	int	i;

	i = 1;
	ft_check_top_and_bottom(0, so_long);
	ft_check_top_and_bottom(so_long->map.line_count - 1, so_long);
	while (i < so_long->map.line_count - 1)
	{
		if (so_long->map.map[i][0] != '1'
			|| so_long->map.map[i][ft_strlen(so_long->map.map[0]) - 2] != '1')
			ft_print_error(ERROR_EDGES, so_long);
		i++;
	}
}

static void	ft_check_is_rectangle(t_so_long *so_long)
{
	int		i;
	size_t	j;

	i = 0;
	j = 0;
	so_long->map.line_len = ft_strlen(so_long->map.map[i]) - 1;
	while (so_long->map.map[i])
	{
		while (so_long->map.map[i][j] && so_long->map.map[i][j] != '\n')
			j++;
		if (j != so_long->map.line_len)
			ft_print_error(ERROR_NOT_A_RECTANGLE, so_long);
		j = 0;
		i++;
	}
}

static void	ft_count_chars(t_so_long *so_long)
{
	while (so_long->map.map[so_long->y])
	{
		while (so_long->map.map[so_long->y][so_long->x])
		{
			if (so_long->map.map[so_long->y][so_long->x] == 'E')
				so_long->map.count_e++;
			else if (so_long->map.map[so_long->y][so_long->x] == 'P')
			{
				so_long->map.count_p++;
				so_long->player_x = so_long->x;
				so_long->player_y = so_long->y;
			}
			else if (so_long->map.map[so_long->y][so_long->x] == 'C')
				so_long->map.count_c++;
			so_long->x++;
		}
		so_long->x = 0;
		so_long->y++;
	}
	if (!so_long->map.count_c || !so_long->map.count_e || !so_long->map.count_p)
		ft_print_error(ERROR_MISSING_CHARS, so_long);
	if (so_long->map.count_p > 1)
		ft_print_error(ERROR_TOO_MANY_PLAYERS, so_long);
}

void	ft_check_map(t_so_long *so_long)
{
	int		i;
	size_t	j;

	i = 0;
	j = 0;
	while (so_long->map.map[i])
	{	
		while (j < ft_strlen(so_long->map.map[i]) - 1)
		{
			if (!ft_strchr("01CEP", so_long->map.map[i][j]))
				ft_print_error(ERROR_OTHER_CHARS, so_long);
			j++;
		}
		j = 0;
		i++;
	}
	ft_count_chars(so_long);
	ft_check_is_rectangle(so_long);
	ft_check_edges(so_long);
}
