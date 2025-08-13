/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 08:56:17 by krepo             #+#    #+#             */
/*   Updated: 2025/08/12 15:31:44 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	setup_input(t_app *fdf)
{
	mlx_key_hook(fdf->win, key_press, fdf);
	mlx_mouse_hook(fdf->win, mouse_press, fdf);
	mlx_hook(fdf->win, 17, 0, close_win, fdf);
}

int	mouse_press(int button, int x, int y, void *param)
{
	t_app	*fdf;

	fdf = (t_app *)param;
	if (button == 4)
	{
		fdf->zoom += 1.0f;
		refresh_win(fdf);
	}
	if (button == 5)
	{
		if (fdf->zoom <= 1.0f)
			return (0);
		fdf->zoom -= 1.0f;
		refresh_win(fdf);
	}
	(void)x;
	(void)y;
	return (0);
}

int	close_win(void *param)
{
	t_app	*fdf;

	fdf = (t_app *)param;
	exit_success(fdf);
	return (0);
}

int	key_press(int keycode, void *param)
{
	t_app	*fdf;

	fdf = (t_app *)param;
	if (keycode == ESC_KEY)
		exit_success(fdf);
	if (keycode == RESET_KEY)
		reset_view(fdf);
	if (keycode == Q_KEY || keycode == E_KEY)
		change_z_scale(fdf, keycode);
	if (keycode == W_KEY || keycode == UP_KEY
		|| keycode == S_KEY || keycode == DOWN_KEY
		|| keycode == A_KEY || keycode == LEFT_KEY
		|| keycode == D_KEY || keycode == RIGHT_KEY)
		move_view(fdf, keycode);
	if (keycode == R_KEY || keycode == F_KEY)
		rotate_view(fdf, keycode);
	return (0);
}
