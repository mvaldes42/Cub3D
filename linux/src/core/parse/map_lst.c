/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 17:56:01 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/19 19:03:59 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	create_map_lst(t_scene *scene_p, char *f_line, int fd, int ret)
{
	while (ret > 0 && f_line[0] == '\0')
		ret = get_next_line(fd, &f_line);
	while (ret > 0)
	{
		if (f_line[0] == '\0')
			exit_message_failure(12);
		ft_lstadd_back_map(&(scene_p->map), f_line);
		ft_putstr_fd(f_line, 1);
		ret = get_next_line(fd, &f_line);
	}
	if (ret == 0 && f_line[0] != '\0')
	{
		scene_p->lline = ft_lstnew_map(f_line);
		ft_lstadd_back_map(&(scene_p->map), scene_p->lline);
	}
}

void		cvt_lst_to_array(t_scene *scene_p, char *f_line, int fd, int ret)
{
	t_map	*current_line;
	int		i;
	int		j;
	int		mx_line;

	create_map_lst(scene_p, f_line, fd, ret);
	//print_map(scene_p->map);
	scene_p->map_a = malloc(ft_lstsize_map(scene_p->map) * sizeof(char*));
	current_line = scene_p->map;
	mx_line = get_max_line(scene_p->map);
	i = -1;
	while (current_line != NULL)
	{
		j = -1;
		scene_p->map_a[++i] = malloc((mx_line + 1) * sizeof(char));
		while (++j < mx_line)
		{
			if (j < (int)ft_strlen(current_line->line))
				scene_p->map_a[i][j] = current_line->line[j];
			else
				scene_p->map_a[i][j] = ' ';
		}
		scene_p->map_a[i][mx_line] = '\0';
		current_line = current_line->next;
	}
	//ft_lstclear_map(&current_line);
}
