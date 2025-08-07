/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:10:19 by krepo             #+#    #+#             */
/*   Updated: 2025/08/07 13:29:16 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	free_matrix(t_app *fdf, t_pixel **space);

void	exit_success(t_app *fdf)
{
	if (fdf)
		free_memory(fdf);
	exit(0);
}

void	exit_error(t_app *fdf, int error)
{
	if (fdf)
		free_memory(fdf);
	if (error == FILETYPE_ERR)
		ft_putstr_fd("Error: Invalid file type. Must be .fdf\n", 2);
	else if (error == FD_ERR)
		perror("Error: open");
	else if (error == FDF_STRUCT_ERR)
		perror("Error: malloc for fdf struct");
	else if (error == MLX_INIT_ERR)
		perror("Error: mlx_init");
	else if (error == MLX_WIN_ERR)
		perror("Error: mlx_win");
	else if (error == MLX_IMG_ERR)
		perror("Error: mlx_new_image");
	else if (error == PARSING_ERR)
		ft_putstr_fd("Error: Invalid map contents or structure.\n", 2);
	else if (error == GET_NEXT_LINE_ERR)
		ft_putstr_fd("Error: gett_next_line failed.\n", 2);
	exit(1);
}

void	free_memory(t_app *fdf)
{
	if (!fdf)
		return ;
	if (fdf->img)
		mlx_destroy_image(fdf->mlx, fdf->img);
	if (fdf->mlx_win)
		mlx_destroy_window(fdf->mlx, fdf->mlx_win);
	if (fdf->mlx)
	{
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
	}
	if (fdf->world)
		free_matrix(fdf, fdf->world);
	if (fdf->screen)
		free_matrix(fdf, fdf->screen);
	free(fdf);
	get_next_line(-2);
}

static void	free_matrix(t_app *fdf, t_pixel **space)
{
	int	i;

	if (!fdf || !space)
		return ;
	i = 0;
	while (i < fdf->matrix_height)
		free(space[i++]);
	free(space);
}

void	reset_img(t_app *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img)
		exit_error(fdf, MLX_IMG_ERR);
	fdf->img_pixels = mlx_get_data_addr(
		fdf->img, &fdf->bpp, &fdf->line_len, &fdf->endian);
	if (!fdf->img_pixels)
		exit_error(fdf, MLX_IMG_ERR);
}
