/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 17:56:01 by mvaldes           #+#    #+#             */
/*   Updated: 2020/07/08 14:42:03 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	create_map_lst(t_scene *scene_ptr, char *f_line, int fd, int ret)
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
		ft_lstadd_back_map(&(scene_ptr->map), tmp);
		ret = get_next_line(fd, &f_line);
	}
}

void	cvt_lst_to_array(t_scene *scene_ptr, char *f_line, int fd, int ret)
{
	t_map	*current_line;
	int		i;

	create_map_lst(scene_ptr, f_line, fd, ret);
	scene_ptr->map_a = malloc(sizeof(char*) * ft_lstsize_map(scene_ptr->map) + 1);
	current_line = scene_ptr->map;
	i = 0;
	while (current_line != NULL)
	{
		scene_ptr->map_a[i] = ft_strdup(current_line->line);
		i++;
		current_line = current_line->next;
	}
}
