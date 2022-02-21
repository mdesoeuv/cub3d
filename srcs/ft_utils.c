/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 18:15:27 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/21 18:30:44 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_get_map_width(char **map)
{
	int		tab_size;
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (map[++i])
	{
		while (map[i][++j])
			if (i == 1 || j > tab_size)
				tab_size = j;
		j = -1;
	}
	return (tab_size);
}
