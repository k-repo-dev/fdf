/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:18:16 by krepo             #+#    #+#             */
/*   Updated: 2025/08/07 12:36:04 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static t_pixel	project_point(t_app *fdf, t_pixel point);

void	calculate_projection_and_update_bounds(t_app *fdf)
{
	int		x;
	int		y;
	t_pixel	projected;

	y = 0;
	while (y < fdf->matrix_height)
	{
		x = 0;
		while (x < fdf->matrix_width)
		{
			projected = project_point(fdf, fdf->world[y][x]);
			fdf->screen[y][x].x = projected.x;
			fdf->screen[y][x].y = projected.y;
			if (projected.x < fdf->proj_min_x)
				fdf->proj_min_x = projected.x;
			if (projected.x > fdf->proj_max_x)
				fdf->proj_max_x = projected.x;
			if (projected.y < fdf->proj_min_y)
				fdf->proj_min_y = projected.y;
			if (projected.y > fdf->proj_max_y)
				fdf->proj_max_y = projected.y;
			x++;
		}
		y++;
	}
}

static t_pixel	project_point(t_app *fdf, t_pixel point)
{
	point.x -= (fdf->matrix_width - 1) / 2.0;
	point.y -= (fdf->matrix_height - 1) / 2.0;
	point.z *= fdf->z_scalar;
	rotate_z(&point, fdf->z_rot_angle);
	rotate_y(&point, fdf->y_rot_angle);
	rotate_x(&point, fdf->x_rot_angle);
	point.x = (point.x - point.y);
	point.y = (point.x + point.y) - point.z;
	point.x *= fdf->img_scalar;
	point.y *= fdf->img_scalar;
	return (point);
}

void	calculate_centering_offset(t_app *fdf)
{
	float	map_width_proj;
	float	map_height_proj;
	float	win_x_mid;
	float	win_y_mid;

	map_width_proj = fdf->proj_max_x - fdf->proj_min_x;
	map_height_proj = fdf->proj_max_x - fdf->proj_min_y;
	map_width_proj = fdf->proj_min_x + map_width_proj / 2.0f;
	map_height_proj = fdf->proj_min_x + map_height_proj / 2.0f;
	win_x_mid = WIN_WIDTH / 2.0f;
	win_y_mid = WIN_HEIGHT / 2.0f;
	fdf->x_move_view = win_x_mid - map_width_proj;
	fdf->y_move_view = win_y_mid - map_height_proj;
}
