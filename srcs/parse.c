/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:25:44 by krepo             #+#    #+#             */
/*   Updated: 2025/08/07 10:46:22 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	parse_lines(t_app *fdf);
static void	parse_split_line(t_app *fdf, char **split_line, int y);
static void	free_str_arr(char ***arr);

t_pixel	**parse_fdf_file(t_app *fdf)
{
	count_matrix_dimensions(fdf);
	if (fdf->matrix_height == 0 || fdf->matrix_width == 0)
		exit_error(fdf, PARSING_ERR);
	fdf->world = init_pixel_matrix(fdf);
	if (!fdf->world)
		exit_error(fdf, MALLOC_ERR);
	fdf->screen = init_pixel_matrix(fdf);
	if (!fdf->screen)
		exit_error(fdf, MALLOC_ERR);
	parse_lines(fdf);
	return (fdf->world);
}

static void	parse_lines(t_app *fdf)
{
	int		fd;
	char	*line;
	int		y;

	fd = open(fdf->file_path, O_RDONLY);
	if (fd == -1)
		exit_error(fdf, FD_ERR);
	y = 0;
	while (y < fdf->matrix_height)
	{
		line = get_next_line(fd);
		if (!line)
			exit_error(fdf, GET_NEXT_LINE_ERR);
		parse_split_line(fdf, ft_split(line, ' '), y);
		free(line);
		y++;
	}
	close(fd);
}

static void	parse_split_line(t_app *fdf, char **split_line, int y)
{
	int		x;
	char	**tmp;
	int		val;

	if (!split_line)
		exit_error(fdf, PARSING_ERR);
	x = 0;
	while (split_line[x])
	{
		tmp = ft_split(split_line[x], ',');
		if (!tmp || !tmp[0])
		{
			free_str_arr(&split_line);
			exit_error(fdf, PARSING_ERR);
		}
		val = ft_atoi_safe(tmp[0]);
		if (!val)
		{
			free_str_arr(&split_line);
			free_str_arr(&tmp);
			exit_error(fdf, PARSING_ERR);
		}
		save_pixel_coordinates(fdf->world, x, y, val);
		free_str_arr(&tmp);
		x++;
	}
	free_str_arr(&split_line);
}

static void	free_str_arr(char ***arr)
{
	int	i;

	if (!*arr)
		return ;
	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}
