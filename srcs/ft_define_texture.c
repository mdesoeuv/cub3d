/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_define_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:26:01 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/21 17:28:39 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_define_texture_3(t_cub3d *cub3d, char **tab)
{
	if (ft_strncmp(tab[0], "SO", 2) == 0)
	{
		if (!cub3d->texture_s)
			cub3d->texture_s = ft_strdup(tab[1]);
		else
			return (1);
	}
	else if (ft_strncmp(tab[0], "WE", 2) == 0)
	{
		if (!cub3d->texture_w)
			cub3d->texture_w = ft_strdup(tab[1]);
		else
			return (1);
	}
	else if (ft_strncmp(tab[0], "EA", 2) == 0)
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
	else if (ft_strncmp(tab[0], "NO", 2) == 0)
	{
		if (!cub3d->texture_n)
			cub3d->texture_n = ft_strdup(tab[1]);
		else
			return (1);
	}
	return (ft_define_texture_3(cub3d, tab));
}

static void	ft_free_define_texture(t_cub3d *cub3d,
	char *line, char **tab, char *error_msg)
{
	free (line);
	ft_free_split(tab);
	close(cub3d->map.fd);
	ft_print_error(error_msg, cub3d);
}

void	ft_define_texture(t_cub3d *cub3d, char *line)
{
	int		i;
	char	**tab;

	i = 0;
	tab = ft_split(line, ' ');
	if (!tab)
		ft_print_error(ERROR_MALLOC, cub3d);
	if (!tab[0])
	{
		ft_free_split(tab);
		return ;
	}
	while (tab[i])
		i++;
	if (i > 2 || i == 1)
		ft_free_define_texture(cub3d, line,
			tab, ERROR_INVALID_TEXTURE_ARG_NAME);
	if (ft_define_texture_2(cub3d, tab))
		ft_free_define_texture(cub3d, line,
			tab, ERROR_TEXTURE_DEFINED_TWICE);
	ft_free_split(tab);
}
