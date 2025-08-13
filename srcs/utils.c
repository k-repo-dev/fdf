/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krepo <krepo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:58:13 by krepo             #+#    #+#             */
/*   Updated: 2025/08/13 09:37:07 by krepo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	skip_whitespace_and_sign(const char **nptr, int *sign);

void	trim_trailing_whitespace(char *str)
{
	int	len;

	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'
			|| str[len -1] == '\n'))
	{
		str[len - 1] = '\0';
		len--;
	}
}

bool	ft_atoi_safe(const char *nptr, int *out)
{
	long long	value;
	int			sign;

	value = 0;
	sign = 1;
	skip_whitespace_and_sign(&nptr, &sign);
	if (!(*nptr >= '0' && *nptr <= '9'))
		return (false);
	while (*nptr >= '0' && *nptr <= '9')
	{
		value = value * 10 + (*nptr - '0');
		if (value > INT_MAX || value < INT_MIN)
			return (false);
		nptr++;
	}
	while (*nptr)
	{
		if (*nptr != ' ' && (*nptr < 9 || *nptr > 13))
			return (false);
		nptr++;
	}
	*out = (int)(value * sign);
	return (true);
}

static void	skip_whitespace_and_sign(const char **nptr, int *sign)
{
	while (**nptr == ' ' || (**nptr >= 9 && **nptr <= 13))
		(*nptr)++;
	if (**nptr == '-' || **nptr == '+')
	{
		if (**nptr == '-')
			*sign = -1;
		(*nptr)++;
	}
}
