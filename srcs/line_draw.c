/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 09:12:08 by krepo             #+#    #+#             */
/*   Updated: 2025/08/11 12:33:13 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	draw_bresenham(t_app *fdf, t_line_vars line);
static void	init_line_vars(t_line_vars *line);

void	draw_lines(t_app *fdf)
{
	t_line_vars	line;
	int			x;
	int			y;

	y = 0;
	while (y < fdf->grid_h)
	{
		x = 0;
		while (x < fdf->grid_w)
		{
			set_line_start(fdf, &line, x, y);
			if (x + 1 < fdf->grid_w)
			{
				set_line_end(fdf, &line, x + 1, y);
				draw_bresenham(fdf, line);
			}
			if (y + 1 < fdf->grid_h)
			{
				set_line_end(fdf, &line, x, y + 1);
				draw_bresenham(fdf, line);
			}
			x++;
		}
		y++;
	}
}

static void	draw_bresenham(t_app *fdf, t_line_vars line)
{
	init_line_vars(&line);
	while (1)
	{
		put_pixel(fdf, line.x0, line.y0, fdf->color);
		if (line.x0 == line.x1 && line.y0 == line.y1)
			break ;
		line.e2 = 2 * line.err;
		if (line.e2 >= line.dy)
		{
			line.err += line.dy;
			line.x0 += line.sx;
		}
		if (line.e2 <= line.dx)
		{
			line.err += line.dx;
			line.y0 += line.sy;
		}
	}
}

static void	init_line_vars(t_line_vars *line)
{
	line->dx = abs(line->x1 - line->x0);
	if (line->x0 < line->x1)
		line->sx = 1;
	else
		line->sx = -1;
	line->dy = -abs(line->y1 - line->y0);
	if (line->y0 < line->y1)
		line->sy = 1;
	else
		line->sy = -1;
	line->err = line->dx + line->dy;
}
