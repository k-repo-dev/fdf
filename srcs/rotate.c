/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:36:16 by krepo             #+#    #+#             */
/*   Updated: 2025/08/07 12:41:37 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	rotaet_x(t_pixel *point, float angle)
{
	float	y;
	float	z;

	y = point->y;
	z = point->z;
	point->y = y * cos(angle) - z * sin(angle);
	point->z = y * sin(angle) + z * cos(angle);
}

void	rotaet_y(t_pixel *point, float angle)
{
	float	x;
	float	z;

	x = point->x;
	z = point->z;
	point->x = x * cos(angle) + z * sin(angle);
	point->z = -x * sin(angle) + z * cos(angle);
}

void	rotaet_z(t_pixel *point, float angle)
{
	float	x;
	float	y;

	x = point->x;
	y = point->y;
	point->x = x * cos(angle) - y * sin(angle);
	point->y = x * sin(angle) + y * cos(angle);
}
