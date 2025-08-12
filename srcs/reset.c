/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:14:25 by krepo             #+#    #+#             */
/*   Updated: 2025/08/11 12:21:28 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	clear_image(t_app *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img)
		exit_error(fdf, MLX_IMG_ERR);
	fdf->pixels = mlx_get_data_addr(
			fdf->img, &fdf->bpp, &fdf->line_len, &fdf->endian);
	if (!fdf->pixels)
		exit_error(fdf, MLX_IMG_ERR);
}

void	reset_view(t_app *fdf)
{
	reset_view_params(fdf);
	refresh_win(fdf);
}
