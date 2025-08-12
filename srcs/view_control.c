/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 09:50:31 by krepo             #+#    #+#             */
/*   Updated: 2025/08/12 10:47:44 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	move_view(t_app *fdf, int keycode)
{
	if (keycode == W_KEY || keycode == UP_KEY)
		fdf->y_offset -= 20;
	if (keycode == S_KEY || keycode == DOWN_KEY)
		fdf->y_offset += 20;
	if (keycode == A_KEY || keycode == LEFT_KEY)
		fdf->x_offset -= 20;
	if (keycode == D_KEY || keycode == RIGHT_KEY)
		fdf->x_offset += 20;
	refresh_win(fdf);
}

void	rotate_view(t_app *fdf, int keycode)
{
	if (keycode == R_KEY)
		fdf->y_angle -= 5;
	if (keycode == F_KEY)
		fdf->y_angle += 5;
	refresh_win(fdf);
}

void	reset_view_params(t_app *fdf)
{
	fdf->zoom = 10.0f;
	fdf->z_scale = 0.1f;
	fdf->x_center_offset = 0;
	fdf->y_center_offset = 0;
	fdf->x_offset = 0;
	fdf->y_offset = 0;
	fdf->x_angle = 30.0f;
	fdf->y_angle = 30.0f;
	fdf->min_x_proj = FLT_MAX;
	fdf->max_x_proj = FLT_MIN;
	fdf->min_y_proj = FLT_MAX;
	fdf->max_y_proj = FLT_MIN;
}

void	change_z_scale(t_app *fdf, int keycode)
{
	if (keycode == Q_KEY)
		fdf->z_scale += 0.1f;
	if (keycode == E_KEY)
		fdf->z_scale -= 0.1f;
	refresh_win(fdf);
}
