/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:08:38 by krepo             #+#    #+#             */
/*   Updated: 2025/08/12 10:47:03 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static t_app	*init_fdf(char *file_path);
static bool		is_fdf_file(const char *filename);
static void		init_mlx(t_app *fdf);

int	main(int ac, char *av[])
{
	t_app	*fdf;

	if (ac != 2 || av[1][0] == '\0')
		return (1);
	if (!is_fdf_file(av[1]))
		exit_error(NULL, FILETYPE_ERR);
	fdf = init_fdf(av[1]);
	if (!fdf)
		exit_error(fdf, FDF_STRUCT_ERR);
	parse_map(fdf);
	render_frame(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	mlx_loop(fdf->mlx);
	exit_success(fdf);
	return (0);
}

void	put_pixel(t_app *fdf, int x, int y, int color)
{
	char	*pixel;
	int		offset;

	if (x < WIN_WIDTH && x >= 0 && y < WIN_HEIGHT && y >= 0)
	{
		offset = (x * (fdf->bpp / 8)) + (y * fdf->line_len);
		pixel = fdf->pixels + offset;
		*(unsigned int *)pixel = color;
	}
}

static t_app	*init_fdf(char *file_path)
{
	t_app	*fdf;

	fdf = (t_app *)ft_calloc(1, sizeof(t_app));
	if (!fdf)
		exit_error(fdf, FDF_STRUCT_ERR);
	init_mlx(fdf);
	fdf->file_path = file_path;
	fdf->world = NULL;
	fdf->screen = NULL;
	fdf->grid_h = 0;
	fdf->grid_w = 0;
	fdf->color = 0xFFFFFF;
	reset_view_params(fdf);
	setup_input(fdf);
	return (fdf);
}

static void	init_mlx(t_app *fdf)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		exit_error(fdf, MLX_INIT_ERR);
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF-Wireframe");
	if (!fdf->win)
		exit_error(fdf, MLX_WIN_ERR);
	fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img)
		exit_error(fdf, MLX_IMG_ERR);
	fdf->pixels = mlx_get_data_addr(
			fdf->img, &fdf->bpp, &fdf->line_len, &fdf->endian);
	if (!fdf->pixels)
		exit_error(fdf, MLX_IMG_ERR);
}

static bool	is_fdf_file(const char *filename)
{
	int	strlen;

	strlen = ft_strlen(filename);
	if (strlen < 4)
		return (false);
	if (!ft_strncmp(filename + strlen - 4, ".fdf", 4))
		return (true);
	else
		return (false);
}
