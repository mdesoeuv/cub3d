/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_define_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:26:01 by vchevill          #+#    #+#             */
/*   Updated: 2022/10/21 17:17:36 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_define_texture_3(t_cub3d *cub3d, char **tab)
{
	if (ft_strncmp(tab[0], "SO", 2) == 0)
	{
		if (!cub3d->texture_s.ptr)
			ft_init_texture(cub3d, tab[1], &(cub3d->texture_s), 's');
		else
			return (1);
	}
	if (ft_strncmp(tab[0], "WE", 2) == 0)
	{
		if (!cub3d->texture_w.ptr)
			ft_init_texture(cub3d, tab[1], &(cub3d->texture_w), 'w');
		else
			return (1);
	}
	else if (ft_strncmp(tab[0], "EA", 2) == 0)
	{
		if (!cub3d->texture_e.ptr)
			ft_init_texture(cub3d, tab[1], &(cub3d->texture_e), 'e');
		else
			return (1);
	}
	return (0);
}

static void	ft_define_colors(t_cub3d *cub3d, char *string, int is_ground)
{
	char	**color_split;
	int		i;

	color_split = ft_split(string, ',');
	if (!color_split)
		ft_print_error(ERROR_MALLOC, cub3d);
	i = -1;
	while (color_split[++i])
		;
	if (i == 3 && is_ground)
	{
		cub3d->color_ground[0] = ft_atoi(color_split[0]);
		cub3d->color_ground[1] = ft_atoi(color_split[1]);
		cub3d->color_ground[2] = ft_atoi(color_split[2]);
	}
	else if (i == 3)
	{
		cub3d->color_ceiling[0] = ft_atoi(color_split[0]);
		cub3d->color_ceiling[1] = ft_atoi(color_split[1]);
		cub3d->color_ceiling[2] = ft_atoi(color_split[2]);
	}	
	ft_free_split(color_split);
	if (i != 3)
		ft_print_error(ERROR_INVALID_COLOR, cub3d);
}

static int	ft_define_texture_2(t_cub3d *cub3d, char **tab)
{
	if (tab[0][0] == 'C')
	{
		if (cub3d->color_ceiling[0] == -1)
			ft_define_colors(cub3d, tab[1], 0);
		else
			return (1);
	}
	else if (tab[0][0] == 'F')
	{
		if (cub3d->color_ground[0] == -1)
			ft_define_colors(cub3d, tab[1], 1);
		else
			return (1);
	}
	else if (ft_strncmp(tab[0], "NO", 2) == 0)
	{
		if (!cub3d->texture_n.ptr)
			ft_init_texture(cub3d, tab[1], &(cub3d->texture_n), 'n');
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
