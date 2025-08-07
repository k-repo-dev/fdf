/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:50:37 by krepo             #+#    #+#             */
/*   Updated: 2025/08/07 12:59:46 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	inti_hooks(t_app *fdf)
{
	mlx_key_hook(fdf->mlx_win, keypress_hook, fdf);
	mlx_mouse_hook(fdf->mlx_win, mouse_hook, fdf);
	mlx_hook(fdf->mlx_win, 17, 0, destroy_notify_hook, fdf);
}

int	mouse_hook(int button, int x, int y, void *param)
{
	t_app	*fdf;

	fdf = (t_app *)param;
	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
		zoom_view(fdf, button);
	(void)x;
	(void)y;
	return (0);
}

int	destroy_notify_hook(void *param)
{
	t_app	*fdf;

	fdf = (t_app *)param;
	exit_success(fdf);
	return (0);
}

int	keypress_hoo(int keycode, void *param)
{
	t_app	*fdf;

	fdf = (t_app *)param;
	if (keycode == ESC_KEY)
		exit_success(fdf);
	if (keycode == RESET_KEY)
		reset_view(fdf);
	if (keycode == W_KEY || keycode == S_KEY || keycode == A_KEY
		|| keycode == D_KEY || keycode == UP_KEY || keycode == DOWN_KEY
		|| keycode == LEFT_KEY || keycode == RIGHT_KEY)
		move_view(fdf, keycode);
	if (keycode == Q_KEY || keycode == E_KEY || keycode == R_KEY
		|| keycode == F_KEY || keycode == T_KEY || keycode == G_KEY)
		rotate_view(fdf, keycode);
	update_img(fdf);
	return (0);
}
