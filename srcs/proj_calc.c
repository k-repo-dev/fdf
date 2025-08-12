/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proj_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:45:05 by krepo             #+#    #+#             */
/*   Updated: 2025/08/12 10:36:27 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static float	calc_x_proj(t_app *fdf, int x, int y);
static float	calc_y_proj(t_app *fdf, int x, int y, int z);

void	calc_projection(t_app *fdf, int x, int y)
{
	float	z;
	float	x_proj;
	float	y_proj;

	z = fdf->world[y][x].z * fdf->z_scale;
	fdf->screen[y][x].z = z;
	x_proj = calc_x_proj(fdf, x, y);
	y_proj = calc_y_proj(fdf, x, y, z);
	x_proj *= fdf->zoom;
	y_proj *= fdf->zoom;
	fdf->screen[y][x].x = x_proj;
	fdf->screen[y][x].y = y_proj;
}

void	calc_bounds(t_app *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->grid_h)
	{
		x = 0;
		while (x < fdf->grid_w)
		{
			calc_projection(fdf, x, y);
			if (fdf->screen[y][x].x < fdf->min_x_proj)
				fdf->min_x_proj = fdf->screen[y][x].x;
			if (fdf->screen[y][x].x > fdf->max_x_proj)
				fdf->max_x_proj = fdf->screen[y][x].x;
			if (fdf->screen[y][x].y < fdf->min_y_proj)
				fdf->min_y_proj = fdf->screen[y][x].y;
			if (fdf->screen[y][x].y > fdf->max_y_proj)
				fdf->max_y_proj = fdf->screen[y][x].y;
			x++;
		}
		y++;
	}
}

void	calc_center_offset(t_app *fdf)
{
	float	map_width_proj;
	float	map_height_proj;
	float	win_x_mid;
	float	win_y_mid;

	map_width_proj = fdf->max_x_proj - fdf->min_x_proj;
	map_height_proj = fdf->max_y_proj - fdf->min_y_proj;
	map_width_proj = fdf->min_x_proj + map_width_proj / 2.0f;
	map_height_proj = fdf->min_y_proj + map_height_proj / 2.0f;
	win_x_mid = WIN_WIDTH / 2.0f;
	win_y_mid = WIN_HEIGHT / 2.0f;
	fdf->x_center_offset = win_x_mid - map_width_proj + fdf->x_offset;
	fdf->y_center_offset = win_y_mid - map_height_proj + fdf->y_offset;
}

static float	calc_x_proj(t_app *fdf, int x, int y)
{
	float	x_proj;

	x_proj = (x - y) * cosf(deg_to_rad(fdf->x_angle));
	return (x_proj);
}

static float	calc_y_proj(t_app *fdf, int x, int y, int z)
{
	float	y_proj;

	y_proj = (x + y) * sinf(deg_to_rad(fdf->y_angle)) - z;
	return (y_proj);
}
