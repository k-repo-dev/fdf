/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_view.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:00:02 by krepo             #+#    #+#             */
/*   Updated: 2025/08/07 13:10:07 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	move_view(t_app *fdf, int keycode)
{
	if (keycode == W_KEY || keycode == UP_KEY)
		fdf->y_move_view += 20;
	if (keycode == S_KEY || keycode == DOWN_KEY)
		fdf->y_move_view -= 20;
	if (keycode == A_KEY || keycode == LEFT_KEY)
		fdf->x_move_view += 20;
	if (keycode == D_KEY || keycode == RIGHT_KEY)
		fdf->x_move_view -= 20;
}

void	zoom_view(t_app *fdf, int button)
{
	if (button == MOUSE_SCROLL_UP)
	{
		fdf->img_scalar += 1;
		if (fdf->img_scalar > 100)
			fdf->img_scalar = 100;
	}
	if (button == MOUSE_SCROLL_DOWN)
	{
		fdf->img_scalar -= 1;
		if (fdf->img_scalar < 1)
			fdf->img_scalar = 1;
	}
	update_img(fdf);
}

void	rotate_view(t_app *fdf, int keycode)
{
	if (keycode == Q_KEY)
		fdf->z_rot_angle -= 0.1;
	if (keycode == E_KEY)
		fdf->z_rot_angle += 0.1;
	if (keycode == R_KEY)
		fdf->x_rot_angle -= 0.1;
	if (keycode == F_KEY)
		fdf->x_rot_angle += 0.1;
	if (keycode == T_KEY)
		fdf->y_rot_angle -= 0.1;
	if (keycode == G_KEY)
		fdf->y_rot_angle += 0.1;
}

void	reset_view_settings(t_app *fdf)
{
	fdf->img_scalar = 20.0f;
	fdf->z_scalar = 0.5f;
	fdf->x_move_view = 0;
	fdf->y_move_view = 0;
	fdf->x_rot_angle = X_ROT_DEFAULT_RAD;
	fdf->y_rot_angle = Y_ROT_DEFAULT_RAD;
	fdf->z_rot_angle = Z_ROT_DEFAULT_RAD;
	fdf->proj_min_x = FLT_MAX;
	fdf->proj_max_x = FLT_MIN;
	fdf->proj_min_y = FLT_MAX;
	fdf->proj_max_y = FLT_MIN;
}

void	reset_view(t_app *fdf)
{
	reset_view_settings(fdf);
	update_img(fdf);
}
