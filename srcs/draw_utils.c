/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 08:48:03 by krepo             #+#    #+#             */
/*   Updated: 2025/08/11 10:26:42 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"


float	deg_to_rad(float deg)
{
	return (deg * (M_PI / 180));
}

t_point	**init_point_grid(t_app *fdf)
{
	t_point	**space;
	int		i;

	space = (t_point **)ft_calloc(fdf->grid_h, sizeof(t_point *));
	if (!space)
		exit_error(fdf, MALLOC_ERR);
	i = 0;
	while ( i < fdf->grid_h)
	{
		space[i] = (t_point *)ft_calloc(fdf->grid_w, sizeof(t_point));
		if (!space[i])
			exit_error(fdf, MALLOC_ERR);
		i++;
	}
	return (space);
}
