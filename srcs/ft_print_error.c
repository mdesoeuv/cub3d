/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchevill <vchevill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:03:16 by vchevill          #+#    #+#             */
/*   Updated: 2022/01/20 15:21:51 by vchevill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_free(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
	return ;
}

void	ft_print_error(char *str, t_so_long *so_long)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	if (so_long->map.map)
		ft_free(so_long->map.map);
	exit(1);
}
