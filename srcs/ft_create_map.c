/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:10:49 by vchevill          #+#    #+#             */
/*   Updated: 2022/01/20 14:16:16 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../includes/get_next_line.h"

static void	get_map_content(t_so_long *so_long)
{
	char	*line;
	int		row_nbr;
	int		i;
	size_t	column_nbr;

	row_nbr = 0;
	column_nbr = 0;
	i = 0;
	line = get_next_line(so_long->map.fd);
	while (line)
	{
		so_long->map.map[row_nbr] = ft_calloc(ft_strlen(line) + 1,
				sizeof(char));
		if (!so_long->map.map[row_nbr])
			ft_print_error(ERROR_MALLOC, so_long);
		while (line[i] != '\0')
			so_long->map.map[row_nbr][column_nbr++] = line[i++];
		so_long->map.map[row_nbr++][column_nbr] = '\0';
		column_nbr = 0;
		i = 0;
		free(line);
		line = get_next_line(so_long->map.fd);
	}
	so_long->map.map[row_nbr] = NULL;
}

static int	count_lines_map(t_so_long *so_long)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = 0;
	fd = open(so_long->map.path, O_RDONLY);
	if (fd < 0)
		ft_print_error(ERROR_FILE_OPENING, so_long);
	else
	{
		line = get_next_line(fd);
		while (line)
		{
			line_count++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (line_count);
}

void	ft_create_map(char *path, t_so_long *so_long)
{
	so_long->map.path = path;
	so_long->map.line_count = count_lines_map(so_long);
	so_long->map.map = ft_calloc(so_long->map.line_count + 1, sizeof(char *));
	if (!(so_long->map.map))
		ft_print_error(ERROR_MALLOC, so_long);
	so_long->map.fd = open(path, O_RDONLY);
	if (so_long->map.fd < 0)
		ft_print_error(ERROR_FILE_OPENING, so_long);
	else
	{
		get_map_content(so_long);
		close(so_long->map.fd);
	}
}
