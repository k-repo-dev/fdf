/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:46:40 by krepo             #+#    #+#             */
/*   Updated: 2025/08/13 10:20:45 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	process_line(t_app *fdf, char *line);

int	count_grid_dims(t_app *fdf)
{
	int		fd;
	char	*line;

	fd = open(fdf->file_path, O_RDONLY);
	if (fd == -1)
		exit_error(fdf, FD_ERR);
	line = get_next_line(fd);
	process_line(fdf, line);
	free(line);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		process_line(fdf, line);
		free(line);
	}
	close(fd);
	return (fdf->grid_h);
}

void	count_grid_width(t_app *fdf, char *line)
{
	int	line_width;
	int	i;

	line_width = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\0')
			line_width++;
		while (line[i] != ' ' && line[i] != '\0')
			i++;
		while (line[i] == ' ' && line[i] != '\0')
			i++;
		if (line[i] == '-' || line[i] == '+')
			i++;
		if (!ft_strncmp(&line[i], "\n", 2) && (line[i + 1]) == '\0')
			i++;
	}
	if (line_width > fdf->grid_w)
		fdf->grid_w = line_width;
}

void	save_point_coords(t_point **space, int x, int y, int z)
{
	if (!space)
		return ;
	space[y][x].x = x;
	space[y][x].y = y;
	space[y][x].z = z;
}

bool	parse_coords(t_app *fdf, char **coords, int x, int y)
{
	int	val;

	if (!ft_atoi_safe(coords[0], &val))
		return (false);
	save_point_coords(fdf->world, x, y, val);
	return (true);
}

static void	process_line(t_app *fdf, char *line)
{
	if (line)
	{
		count_grid_width(fdf, line);
		fdf->grid_h++;
	}
	else
		exit_error(fdf, GET_NEXT_LINE_ERR);
}
