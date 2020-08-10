/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 17:57:33 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/10 18:49:55 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	is_border_closed(char **map_a, int i, int j)
{
	if (i == 0 && map_a[i][j] == '0')
		return (0);
	if (map_a[i + 1] == NULL && map_a[i][j] == '0')
		return (0);
	if ((map_a[i][0] == '0') || (map_a[i][j] == '0' && map_a[i][j + 1] == '\0'))
		return (0);
	return (1);
}

static int	are_holes_closed(char **map_a, int i, int j)
{
	if (j != 0)
	{
		if ((map_a[i][j - 1] == '0') ||
		(i != 0 && map_a[i - 1][j - 1] == '0') ||
		(map_a[i + 1] != NULL && j - 1 < (int)ft_strlen(map_a[i + 1])
		&& map_a[i + 1][j - 1] == '0'))
		{
			if (map_a[i + 1] != NULL && map_a[i + 1][j - 1] == '0')
				printf("i: %d & j: %d\n", i, j);
			return (0);
		}
	}
	if (map_a[i][j + 1])
	{
		if ((map_a[i][j + 1] == '0') ||
		(i != 0 && map_a[i - 1][j + 1] == '0') ||
		(map_a[i + 1] != NULL && j + 1 < (int)ft_strlen(map_a[i + 1])
		&& map_a[i + 1][j + 1] == '0'))
			return (0);
	}
	if ((i != 0 && map_a[i - 1][j] == '0') ||
	(map_a[i + 1] != NULL && j < (int)ft_strlen(map_a[i + 1])
	&& map_a[i + 1][j] == '0'))
		return (0);
	return (1);
}

int			is_map_closed(char **map_a)
{
	int		i;
	int		j;

	i = 0;
	g_error = 6;
	while (map_a[i])
	{
		j = 0;
		while (map_a[i][j])
		{
			if (!is_border_closed(map_a, i, j))
				return (0);
			if (map_a[i][j] == ' ' && !are_holes_closed(map_a, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int			parse_map(char **map)
{
	int		i;
	int		j;
	int		position;

	position = 0;
	g_error = 7;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_strrchr("012NSEW ", map[i][j]))
				return (0);
			if (ft_strrchr("NSEW", map[i][j]))
				position++;
			j++;
		}
		i++;
	}
	if (position != 1)
		return (0);
	return (1);
}
