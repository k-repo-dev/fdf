/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:46:40 by krepo             #+#    #+#             */
/*   Updated: 2025/08/07 10:58:17 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	count_matrix_dimensions(t_app *fdf)
{
	int		fd;
	char	*line;

	fd = open(fdf->file_path, O_RDONLY);
	if (fd == -1)
		exit_error(fdf, FD_ERR);
	line = get_next_line(fd);
	if (line)
	{
		fdf->matrix_height++;
		count_matrix_width(fdf, line);
		free(line);
	}
	while ((line = get_next_line(fd)))
	{
		count_matrix_width(fdf, line);
		fdf->matrix_height++;
		free(line);
	}
	close(fd);
	return (fdf->matrix_height);
}

void	count_matrix_width(t_app *fdf, char *line)
{
	char	**split;
	int		count;

	split = ft_split(line, ' ');
	if (!split)
		exit_error(fdf, PARSING_ERR);
	count = 0;
	while (split[count])
	{
		free(split[count]);
		count++;
	}
	free(split);
	if (fdf->matrix_height == 1)
		fdf->matrix_width = count;
	else if (count != fdf->matrix_width)
	{
		ft_putstr_fd("Error: Inconsistent row width.\n", 2);
	exit_error(fdf, PARSING_ERR);
	}
}

t_pixel	**init_pixel_matrix(t_app *fdf)
{
	t_pixel	**space;
	int		i;

	space = (t_pixel **)malloc(sizeof(t_pixel *) * fdf->matrix_height);
	if (!space)
		exit_error(fdf, MALLOC_ERR);
	i = 0;
	while (i < fdf->matrix_height)
	{
		space[i] = (t_pixel *)malloc(sizeof(t_pixel) * fdf->matrix_width);
		if (!space[i])
			exit_error(fdf, MALLOC_ERR);
		i++;
	}
	return (space);
}

void	save_pixel_coordinate(t_pixel **space, int x, int y, int z)
{
	if (!space)
		return ;
	space[y][x].x = (float)x;
	space[y][x].y = (float)y;
	space[y][x].z = (float)z;
}
