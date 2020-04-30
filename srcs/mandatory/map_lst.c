/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 17:56:01 by mvaldes           #+#    #+#             */
/*   Updated: 2020/04/29 18:52:16 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char		**convert_lst_to_array(t_map *map)
{
	char	**map_a;
	t_map	*current_line;
	int		i;

	map_a = malloc(sizeof(char*) * ft_lstsize_map(map) + 1);
	current_line = map;
	i = 0;
	while (current_line != NULL)
	{
		map_a[i] = ft_strdup(current_line->line);
		i++;
		current_line = current_line->next;
	}
	return (map_a);
}

t_map		*create_map_lst(t_scene scene, char *f_line, int fd, int ret)
{
	t_map	*tmp;

	while (ret > 0 && f_line[0] == '\0')
		ret = get_next_line(fd, &f_line);
	while (ret > 0)
	{
		if (f_line[0] == '\0')
			ret = get_next_line(fd, &f_line);
		if (!(tmp = ft_lstnew_map(ft_strdup(f_line))))
			exit_message_failure();
		ft_lstadd_back_map(&(scene.map), tmp);
		ret = get_next_line(fd, &f_line);
	}
	return (scene.map);
}
