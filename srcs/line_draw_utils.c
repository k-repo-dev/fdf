/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 09:27:18 by krepo             #+#    #+#             */
/*   Updated: 2025/08/11 09:31:27 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	set_line_start(t_app *fdf, t_line_vars *line, int x, int y)
{
	line->x0 = fdf->screen[y][x].x;
	line->y0 = fdf->screen[y][x].y;
}

void	set_line_end(t_app *fdf, t_line_vars *line, int x, int y)
{
	line->x1 = fdf->screen[y][x].x;
	line->y1 = fdf->screen[y][x].y;
}
