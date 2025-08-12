/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:25:44 by krepo             #+#    #+#             */
/*   Updated: 2025/08/11 14:09:28 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	parse_lines(t_app *fdf);
static bool	parse_line_split(t_app *fdf, char **split_line, int y);
static bool	parse_coords(t_app *fdf, char **cords, int x, int y);
static void	free_str_array(char ***arr, int i);

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
	parse_lines(fdf);
	return (fdf->world);
}

static void	parse_lines(t_app *fdf)
{
	int		fd;
	char	*line;
	char	**split_line;
	int		y;

	fd = open(fdf->file_path, O_RDONLY);
	if (fd == -1)
		exit_error(fdf, FD_ERR);
	y = 0;
	while (y < fdf->grid_h)
	{
		line = get_next_line(fd);
		if (!line)
		{
			close(fd);
			exit_error(fdf, GET_NEXT_LINE_ERR);
		}
		split_line = ft_split(line, ' ');
		free(line);
		if (!split_line || !parse_line_split(fdf, split_line, y))
		{
			free_str_array(&split_line, 0);
			close(fd);
			exit_error(fdf, PARSING_ERR);
		}
		free_str_array(&split_line, 0);
		y++;
	}
	close(fd);
}

static bool	parse_line_split(t_app *fdf, char **split_line, int y)
{
	char	**coords;
	int		x;

	x = 0;
	while (x < fdf->grid_w)
	{
		coords = ft_split(split_line[x], ',');
		if (!coords || !coords[0])
		{
			free_str_array(&coords, x);
			return (false);
		}
		if (!parse_coords(fdf, coords, x, y))
		{
			free_str_array(&split_line, x);
			return (false);
		}
		free_str_array(&coords, 0);
		x++;
	}
	return (true);
}

static bool	parse_coords(t_app *fdf, char **coords, int x, int y)
{
	int	tmp_val;
	int	val;

	tmp_val = ft_atoi_safe(coords[0]);
	if (tmp_val == 0 && coords[0][0] != '0')
		return (false);
	val = tmp_val;
	save_point_coords(fdf->world, x, y, val);
	return (true);
}

static void	free_str_array(char ***arr, int i)
{
	if (!*arr)
		return ;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}
