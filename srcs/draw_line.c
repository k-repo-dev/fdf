/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:06:31 by krepo             #+#    #+#             */
/*   Updated: 2025/08/07 12:17:49 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	init_line_calc_struct(t_line_calc *line);

void	draw_line(t_app *fdf, t_pixel p0, t_pixel p1)
{
	t_line_calc	line;
	int			color;

	line.x0 = round(p0.x + fdf->x_move_view);
	line.y0 = round(p0.y + fdf->y_move_view);
	line.x1 = round(p1.x + fdf->x_move_view);
	line.y1 = round(p1.y + fdf->y_move_view);
	init_line_calc_struct(&line);
	color = 0xFFFFFF;
	while (1)
	{
		pixel_to_img(fdf, line.x0, line.y0, color);
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

static void	init_line_calc_struct(t_line_calc *line)
{
	line->dx = abs(line->x1 - line->x0);
	if (line->x0 < line->y1)
		line->sx = 1;
	else
		line->sx = -1;
	line->dy = -abs(line->y1 - line->y0);
	if (line->y0 < line->y1)
		line->sy = 1;
	else
		line->sy =-1;
	line->err = line->dx + line->dy;
}
