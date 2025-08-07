/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:58:28 by krepo             #+#    #+#             */
/*   Updated: 2025/08/07 12:06:06 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	draw_map_lines(t_app *fdf);

void	draw_pixels_on_img(t_app *fdf)
{
	calculate_projection_and_update_bounds(fdf);
	calculate_centering_offset(fdf);
	draw_map_lines(fdf);
}

static void	draw_map_lines(t_app *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->matrix_height)
	{
		x = 0;
		while (x < fdf->matrix_width)
		{
			if (x + 1 < fdf->matrix_width)
				draw_line(fdf, fdf->screen[y][x], fdf->screen[y][x + 1]);
			if (y + 1 < fdf->matrix_height)
				draw_line(fdf, fdf->screen[y][x], fdf->screen[y + 1][x]);
			x++;
		}
		y++;
	}
}

void	update_img(t_app *fdf)
{
	reset_img(fdf);
	draw_pixels_on_img(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->img, 0, 0);
	fdf->proj_min_x = FLT_MAX;
	fdf->proj_max_x = FLT_MIN;
	fdf->proj_min_y = FLT_MAX;
	fdf->proj_max_y = FLT_MIN;
}
