/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 17:57:33 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/13 20:55:55 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	is_border_closed(char **map_a, int i, int j, int size)
{
	char *no_wall;

	no_wall = "02NSEW";
	if (i == 0 && ft_strchr(no_wall, map_a[i][j]))
		return (0);
	if (i == size - 1 && ft_strchr(no_wall, map_a[i][j]))
		return (0);
	if ((ft_strchr(no_wall, map_a[i][0])) || (ft_strchr(no_wall, map_a[i][j])
	&& map_a[i][j + 1] == '\0'))
		return (0);
	return (1);
}

static int	are_holes_closed(char **m, int i, int j, t_scene *s)
{
	char	*n_w;
	int		max;
	int		sz;

	sz = ft_lstsize_map(s->map) - 1;
	max = get_max_line(s->map) - 1;
	n_w = "02NSEW";
	if (i <= sz && j <= max)
	{
		if (j != 0)
		{
			if ((ft_strchr(n_w, m[i][j - 1])) || (i != 0 && ft_strchr(n_w,
			m[i - 1][j - 1])) || (i < sz && (m[i + 1][j - 1] != '\0' &&
			ft_strchr(n_w, m[i + 1][j - 1]))))
				return (0);
		}
		if ((j + 1 <= max) && ((ft_strchr(n_w, m[i][j + 1])) || (i != 0 && ft_strchr(n_w, m[i - 1]
		[j + 1])) || (i < sz && ft_strchr(n_w, m[i + 1][j + 1]))))
			return (0);
		if ((i != 0 && ft_strchr(n_w, m[i - 1][j])) || (i < sz
		&& ft_strchr(n_w, m[i + 1][j])))
			return (0);
	}
	return (1);
}

int			is_map_closed(char **map_a, t_scene *s)
{
	int		i;
	int		j;

	i = 0;
	while (i <= ft_lstsize_map(s->map) - 1)
	{
		j = 0;
		while (map_a[i][j])
		{
			// printf("%c", map_a[i][j]);
			if (!is_border_closed(map_a, i, j, ft_lstsize_map(s->map)))
			{
				// printf("hello\n");
				return (0);
			}
			if (map_a[i][j] == ' ' && !are_holes_closed(map_a, i, j, s))
				return (0);
			j++;
		}
		// printf("\n");
		i++;
	}
	return (1);
}

int			parse_map(char **map, t_scene *s)
{
	int		i;
	int		j;
	int		position;

	position = 0;
	i = 0;
	// printf("size: %d\n", ft_lstsize_map(s->map));
	while (i < ft_lstsize_map(s->map))
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_strrchr("012NSEW ", map[i][j]))
				exit_message_failure(2);
			if (ft_strrchr("NSEW", map[i][j]))
				position++;
			j++;
		}
		i++;
	}
	if (position != 1)
		exit_message_failure(13);
	return (1);
}
