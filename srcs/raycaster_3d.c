/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_3d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesoeuv <mdesoeuv@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 10:13:32 by mdesoeuv          #+#    #+#             */
/*   Updated: 2022/02/23 10:17:59 by mdesoeuv         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


double	ft_ray_length(t_cub3d *cub3d, double angle)
{
	double		v_dy_length;
	double		v_dx_length;
	int			interesec_to_pass_x;
	int			interesec_to_pass_y;
	int			is_x_updated;

	interesec_to_pass_x = 0;
	interesec_to_pass_y = 0;
	is_x_updated = -1;
	
	// dprintf(2, "player angle %f\n", cub3d->player_angle);
	while (cub3d->map.map[(int)(cub3d->player.y / CUBE_SIZE) + interesec_to_pass_y][(int)(cub3d->player.x / CUBE_SIZE) + interesec_to_pass_x] != '1')
	{
		//dprintf(1, "y_to_check=%i\n", (int)(cub3d->player.y / CUBE_SIZE) + interesec_to_pass_y);
		//dprintf(1, "x_to_check=%i\n", (int)(cub3d->player.x / CUBE_SIZE) + interesec_to_pass_x);
		if ( angle > 0 && angle < M_PI && is_x_updated != 1) // vecteur vers le haut (y positif)
		{
			v_dy_length = fabs((CUBE_SIZE - (cub3d->player.y % CUBE_SIZE) + (CUBE_SIZE * abs(interesec_to_pass_y))) / sin(angle));
			// dprintf(1, "dy=%d, angle=%f\n", (CUBE_SIZE - (cub3d->player.y % CUBE_SIZE) + (CUBE_SIZE * abs(interesec_to_pass_y))), angle);
		}
		else if (is_x_updated != 1)// vecteur vers le haut (y negatif)
		{
			v_dy_length = fabs(((cub3d->player.y % CUBE_SIZE) + (CUBE_SIZE * abs(interesec_to_pass_y))) / sin(angle));
			// dprintf(1, "dy=%d, angle=%f\n", (cub3d->player.y % CUBE_SIZE) + (CUBE_SIZE * abs(interesec_to_pass_y)), angle);
		}
		if ( angle > M_PI / 2 && angle < (3 * M_PI)/2 && is_x_updated != 0) // vecteur vers le bas ?? (y positif ?)
		{
			v_dx_length = fabs(((cub3d->player.x % CUBE_SIZE) + (CUBE_SIZE * abs(interesec_to_pass_x))) / cos(angle));
			// dprintf(1, "dx=%d, angle=%f\n", ((cub3d->player.x % CUBE_SIZE) + (CUBE_SIZE * abs(interesec_to_pass_x))), angle);
		}
		else if (is_x_updated != 0) // vecteur vers le haut (y negatif)
		{
			v_dx_length = fabs((CUBE_SIZE - (cub3d->player.x % CUBE_SIZE) + (CUBE_SIZE * abs(interesec_to_pass_x))) / cos(angle));
			// dprintf(1, "dx=%d, angle=%f\n", (CUBE_SIZE - (cub3d->player.x % CUBE_SIZE) + (CUBE_SIZE * abs(interesec_to_pass_x))), angle);
		}
		// dprintf(1, "v_dy_length=%f\n", v_dy_length);
		// dprintf(1, "v_dx_length=%f\n", v_dx_length);

		if (v_dy_length > v_dx_length && !( angle > M_PI / 2 && angle < (3 * M_PI)/2)) // si longueur du vecteur qui s'arrete aux x < a celui qui s'arrete aux y
		{
			is_x_updated = 1;
			interesec_to_pass_x++;
		}
		else if (v_dy_length > v_dx_length)
		{
			is_x_updated = 1;
			interesec_to_pass_x--;
		}
		else if (v_dy_length < v_dx_length && !( angle > 0 && angle < M_PI))
		{
			is_x_updated = 0;
			interesec_to_pass_y--;
		}
		else 
		{
			is_x_updated = 0;
			interesec_to_pass_y++;
		}
	}
	// dprintf(1, "y_to_check=%i\n", (int)(cub3d->player.y / CUBE_SIZE) + interesec_to_pass_y);
	// dprintf(1, "x_to_check=%i\n", (int)(cub3d->player.x / CUBE_SIZE) + interesec_to_pass_x);
	if (v_dy_length > v_dx_length) // la longueur du rayon correspond à celle du vecteur qui a rencontré en premier un obstacle
		return (v_dx_length);
	else 
		return (v_dy_length);
}

void	draw_rays(t_cub3d *cub3d)
{
	int		l;
	double	ray_length;
	double	dx;
	double	dy;
	int		i;
	double	angle_tmp;

	i = -500;
	while ( i < 500)
	{
		angle_tmp = cub3d->player_angle + M_PI / 1980 * i;
		if (angle_tmp > 2 * M_PI)
			angle_tmp -= 2 * M_PI;
		ray_length = ft_ray_length(cub3d, angle_tmp);
		 // dprintf(1, "%f\n", ray_length);
		 // dprintf(1, "-------\n");
		l = 1;
		while (l < ray_length)
		{
			dx = l * cos(angle_tmp);
			dy = l * sin(angle_tmp);
			put_pixel_to_image(cub3d, cub3d->player.x + dx, cub3d->player.y + dy, create_trgb(0, 0, 0, 255));
			l++;
		}
		i++;
	}
}


void	draw_image_3d(t_cub3d *cub3d)
{
	draw_rays(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->window_ptr, \
		cub3d->win_render.pointer, 0, 0);
}