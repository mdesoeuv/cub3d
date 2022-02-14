/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_textures_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 14:24:55 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/14 11:33:08 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/get_next_line.h"

int	ft_all_textures_declared(t_cub3d *cub3d)
{
	if (cub3d->texture_e && cub3d->texture_w
		&& cub3d->texture_n && cub3d->texture_s
		&& cub3d->color_ceiling && cub3d->color_ground)
		return (1);
	else
		return (0);
}

static int	ft_define_texture_3(t_cub3d *cub3d, char **tab)
{
	if (ft_strcmp(tab[0], "SO"))
	{
		if (!cub3d->texture_s)
			cub3d->texture_s = ft_strdup(tab[1]);
		else
			return (1);
	}
	else if (ft_strcmp(tab[0], "WE"))
	{
		if (!cub3d->texture_w)
			cub3d->texture_w = ft_strdup(tab[1]);
		else
			return (1);
	}
	else if (ft_strcmp(tab[0], "EA"))
	{
		if (!cub3d->texture_e)
			cub3d->texture_e = ft_strdup(tab[1]);
		else
			return (1);
	}
	return (0);
}

static int	ft_define_texture_2(t_cub3d *cub3d, char **tab)
{
	if (tab[0][0] == 'C')
	{
		if (!cub3d->color_ceiling)
			cub3d->color_ceiling = ft_strdup(tab[1]);
		else
			return (1);
	}
	else if (tab[0][0] == 'F')
	{
		if (!cub3d->color_ground)
			cub3d->color_ground = ft_strdup(tab[1]);
		else
			return (1);
	}
	else if (ft_strcmp(tab[0], "NO"))
	{
		if (!cub3d->texture_n)
			cub3d->texture_n = ft_strdup(tab[1]);
		else
			return (1);
	}
	return (ft_define_texture_3(cub3d, tab));
}

static void	ft_define_texture(t_cub3d *cub3d, char *line)
{
	int		i;
	char	**tab;

	i = 0;
	tab = ft_split(line, ' ');
	if (!tab)
		ft_print_error(ERROR_MALLOC, cub3d);
	while (tab[i])
		i++;
	if (i > 2 || i == 1)
	{
		free (line);
		ft_free_split(tab);
		close(cub3d->map.fd);
		ft_print_error(ERROR_INVALID_TEXTURE_ARG_NAME, cub3d);
	}
	if (ft_define_texture_2(cub3d, tab))
	{
		free (line);
		ft_free_split(tab);
		close(cub3d->map.fd);
		ft_print_error(ERROR_TEXTURE_DEFINED_TWICE, cub3d);
	}
}

void	get_textures_path(t_cub3d *cub3d)
{
	char	*line;

	cub3d->map.line_start_map_in_cub = 0;
	line = get_next_line(cub3d->map.fd);
	cub3d->map.line_start_map_in_cub++;
	while (line && !ft_all_textures_declared(cub3d))
	{
		dprintf(1,"eee%s",line);
		ft_define_texture(cub3d, line);
		free(line);
		line = get_next_line(cub3d->map.fd);
		dprintf(1,"aaa%s",line);
		cub3d->map.line_start_map_in_cub++;
		if (line == NULL)
		{
			close(cub3d->map.fd);
			ft_print_error(ERROR_MALLOC, cub3d);
		}
	}
	close(cub3d->map.fd);
}
