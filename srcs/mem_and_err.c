/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_and_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 10:04:38 by krepo             #+#    #+#             */
/*   Updated: 2025/08/11 13:41:34 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	free_grid(t_app *fdf, t_point **space);

void	exit_success(t_app *fdf)
{
	if (fdf)
		cleanup(fdf);
	exit(0);
}

void	exit_error(t_app *fdf, int error)
{
	if (fdf)
		cleanup(fdf);
	if (error == FILETYPE_ERR)
		ft_putstr_fd("is_fdf_file: Invalid file type.\n", 2);
	if (error == FD_ERR)
		perror("open");
	if (error == FDF_STRUCT_ERR)
		perror("malloc");
	if (error == MLX_INIT_ERR)
		perror("mlx_init");
	if (error == MLX_WIN_ERR)
		perror("mlx_win");
	if (error == MLX_IMG_ERR)
		perror("mlx_new_img");
	if (error == GRID_ERR)
		ft_putstr_fd("parse_map: Error creating grid.\n", 2);
	if (error == PARSING_ERR)
		ft_putstr_fd("parse_map: Error file contents.\n", 2);
	if (error == GET_NEXT_LINE_ERR)
		ft_putstr_fd("get_next_line: Something went wrong.\n", 2);
	exit(1);
}

void	cleanup(t_app *fdf)
{
	if (!fdf)
		return ;
	if (fdf->img)
		mlx_destroy_image(fdf->mlx, fdf->img);
	if (fdf->win)
		mlx_destroy_window(fdf->mlx, fdf->win);
	if (fdf->mlx)
		mlx_destroy_display(fdf->mlx);
	if (fdf->world)
		free_grid(fdf, fdf->world);
	if (fdf->screen)
		free_grid(fdf, fdf->screen);
	free(fdf);
	get_next_line(-2);
}

static void	free_grid(t_app *fdf, t_point **space)
{
	int	i;

	i = 0;
	if (!fdf || !space)
		return ;
	while (i < fdf->grid_h)
		free(space[i++]);
	free(space);
}
