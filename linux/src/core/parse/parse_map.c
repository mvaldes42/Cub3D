/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 17:57:33 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/19 23:20:58 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int		is_border_closed(char **map_a, int i, int j, int size)
{
	char *no_wall;

	no_wall = "02NSEW";
	if (i == 0 && ft_strchr(no_wall, map_a[i][j]))
		return (0);
	if (i == size - 1 && ft_strchr(no_wall, map_a[i][j]))
		return (0);
	if ((ft_strchr(no_wall, map_a[i][0])) || (ft_strchr(no_wall, map_a[i][j]) &&
	map_a[i][j + 1] == '\0'))
		return (0);
	return (1);
}

static int		are_holes_closed(char **m, int i, int j, t_scene *s)
{
	char	*n_w;

	n_w = "02NSEW";
	if (i < s->map_s && j < s->line_m)
	{
		if (j != 0)
		{
			if ((ft_strchr(n_w, m[i][j - 1])) || (i != 0 && ft_strchr(n_w, m
			[i - 1][j - 1])) || (i < s->map_s - 1 && (m[i + 1][j - 1] != '\0'
			&& ft_strchr(n_w, m[i + 1][j - 1]))))
				return (0);
		}
		if ((j < s->line_m - 1) && ((ft_strchr(n_w, m[i][j + 1])) || (i != 0 &&
			ft_strchr(n_w, m[i - 1][j + 1])) || (i < (s->map_s - 1) &&
			ft_strchr(n_w, m[i + 1][j + 1]))))
			return (0);
		if ((i != 0 && ft_strchr(n_w, m[i - 1][j])) || (i < s->map_s - 1
		&& ft_strchr(n_w, m[i + 1][j])))
			return (0);
	}
	return (1);
}

int				is_map_closed(char **map_a, t_scene *s)
{
	int i;
	int j;

	i = 0;
	while (i < s->map_s)
	{
		j = 0;
		while (map_a[i][j])
		{
			if (!is_border_closed(map_a, i, j, s->map_s))
				return (0);
			if (map_a[i][j] == ' ' && !are_holes_closed(map_a, i, j, s))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int				parse_map(t_env *e, char **map, t_scene *s)
{
	int i;
	int j;
	int position;

	position = 0;
	i = 0;
	while (i < s->map_s)
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_strrchr("012NSEW ", map[i][j]))
				exit_message_failure(2, e, 2);
			if (ft_strrchr("NSEW", map[i][j]))
				position++;
			j++;
		}
		i++;
	}
	if (position != 1)
		exit_message_failure(2, e, 13);
	return (1);
}
