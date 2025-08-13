/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:25:44 by krepo             #+#    #+#             */
/*   Updated: 2025/08/13 10:13:48 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	parse_grid_data(t_app *fdf);
static void	process_grid_line(t_app *fdf, int y, int fd);
static bool	parse_line_split(t_app *fdf, char **split_line, int y);
static bool	parse_and_save_point(t_app *fdf, char *point_str, int x, int y);

t_point	**parse_map(t_app *fdf)
{
	count_grid_dims(fdf);
	if (fdf->grid_h == 0 || fdf->grid_w == 0)
		exit_error(fdf, PARSING_ERR);
	fdf->world = init_point_grid(fdf);
	if (!fdf->world)
		exit_error(fdf, MALLOC_ERR);
	fdf->screen = init_point_grid(fdf);
	if (!fdf->screen)
		exit_error(fdf, MALLOC_ERR);
	parse_grid_data(fdf);
	return (fdf->world);
}

static void	parse_grid_data(t_app *fdf)
{
	int		fd;
	int		y;

	fd = open(fdf->file_path, O_RDONLY);
	if (fd == -1)
		exit_error(fdf, FD_ERR);
	y = 0;
	while (y < fdf->grid_h)
	{
		process_grid_line(fdf, y, fd);
		y++;
	}
	close(fd);
}

static void	process_grid_line(t_app *fdf, int y, int fd)
{
	char	*line;
	char	**split_line;

	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		exit_error(fdf, GET_NEXT_LINE_ERR);
	}
	trim_trailing_whitespace(line);
	split_line = ft_split(line, ' ');
	free(line);
	if (!split_line || !parse_line_split(fdf, split_line, y))
	{
		free_str_array(&split_line, 0);
		close(fd);
		exit_error(fdf, PARSING_ERR);
	}
	free_str_array(&split_line, 0);
}

static bool	parse_line_split(t_app *fdf, char **split_line, int y)
{
	int		x;

	x = 0;
	while (x < fdf->grid_w)
	{
		if (!parse_and_save_point(fdf, split_line[x], x, y))
		{
			free_str_array(&split_line, 0);
			return (false);
		}
		x++;
	}
	return (true);
}

static bool	parse_and_save_point(t_app *fdf, char *point_str, int x, int y)
{
	char	**coords;

	if (!point_str)
	{
		save_point_coords(fdf->world, x, y, 0);
		return (true);
	}
	coords = ft_split(point_str, ',');
	if (!coords || !coords[0])
	{
		free_str_array(&coords, 0);
		return (false);
	}
	if (!parse_coords(fdf, coords, x, y))
	{
		free_str_array(&coords, 0);
		return (false);
	}
	free_str_array(&coords, 0);
	return (true);
}
