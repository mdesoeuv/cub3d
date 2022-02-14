/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:10:49 by vchevill          #+#    #+#             */
/*   Updated: 2022/02/14 10:44:18 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/get_next_line.h"

static char	*go_to_map_first_line(t_cub3d *cub3d)
{
	char	*line;

	line = get_next_line(cub3d->map.fd);
	while (line && (--cub3d->map.line_start_map_in_cub) > 0)
	{
		free(line);
		line = get_next_line(cub3d->map.fd);
	}
	return (line);
}

static void	get_map_content(t_cub3d *cub3d)
{
	char	*line;
	int		row_nbr;
	int		i;
	size_t	column_nbr;

	row_nbr = 0;
	column_nbr = 0;
	i = 0;
	line = go_to_map_first_line(cub3d);
	while (line)
	{
		cub3d->map.map[row_nbr] = ft_calloc(ft_strlen(line) + 1,
				sizeof(char));
		if (!cub3d->map.map[row_nbr])
			ft_print_error(ERROR_MALLOC, cub3d);
		while (line[i] != '\0')
			cub3d->map.map[row_nbr][column_nbr++] = line[i++];
		cub3d->map.map[row_nbr++][column_nbr] = '\0';
		column_nbr = 0;
		i = 0;
		free(line);
		line = get_next_line(cub3d->map.fd);
	}
	cub3d->map.map[row_nbr] = NULL;
}

static int	ft_is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ' )
		i++;
	if (!line[i])
		return (1);
	else
		return (0);
}

static int	count_lines_map(t_cub3d *cub3d)
{
	char	*line;
	int		line_count;
	int		is_empty_line;

	line_count = 0;
	line = get_next_line(cub3d->map.fd);
	cub3d->map.line_start_map_in_cub++;
	while (line && is_empty_line)
	{
		if (!ft_is_empty_line(line))
			break ;
		free(line);
		line = get_next_line(cub3d->map.fd);
		cub3d->map.line_start_map_in_cub++;
	}
	while (line)
	{
		line_count++;
		free(line);
		line = get_next_line(cub3d->map.fd);
	}
	close(cub3d->map.fd);
	return (line_count);
}

void	ft_create_map(char *path, t_cub3d *cub3d)
{
	cub3d->map.path = path;
	cub3d->map.fd = open(path, O_RDONLY);
	if (cub3d->map.fd < 0)
		ft_print_error(ERROR_FILE_OPENING, cub3d);
	else
	{
		get_textures_path(cub3d);
		if (!ft_all_textures_declared(cub3d))
			ft_print_error(ERROR_MISSING_TEXTURES, cub3d);
		cub3d->map.line_count = count_lines_map(cub3d);
		cub3d->map.map = ft_calloc(cub3d->map.line_count + 1, sizeof(char *));
		if (!(cub3d->map.map))
			ft_print_error(ERROR_MALLOC, cub3d);
		cub3d->map.fd = open(path, O_RDONLY);
		if (cub3d->map.fd < 0)
			ft_print_error(ERROR_FILE_OPENING, cub3d);
		get_map_content(cub3d);
	}
}
