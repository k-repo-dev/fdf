/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_points.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 08:38:22 by krepo             #+#    #+#             */
/*   Updated: 2025/08/12 10:35:51 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	render_frame(t_app *fdf)
{
	int	x;
	int	y;

	calc_bounds(fdf);
	calc_center_offset(fdf);
	y = 0;
	while (y < fdf->grid_h)
	{
		x = 0;
		while ( x <fdf->grid_w)
		{
			draw_point(fdf, x, y);
			x++;
		}
		y++;
	}
	draw_lines(fdf);
}

void	draw_point(t_app *fdf, int x, int y)
{
	fdf->screen[y][x].x = round(fdf->screen[y][x].x + fdf->x_center_offset);
	fdf->screen[y][x].y = round(fdf->screen[y][x].y + fdf->y_center_offset);
	put_pixel(fdf, fdf->screen[y][x].x, fdf->screen[y][x].y, fdf->color);
}

void	refresh_win(t_app *fdf)
{
	clear_image(fdf);
	render_frame(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0 , 0);
	fdf->min_x_proj = FLT_MAX;
	fdf->max_x_proj = FLT_MIN;
	fdf->min_y_proj = FLT_MAX;
	fdf->max_y_proj = FLT_MIN;
}
