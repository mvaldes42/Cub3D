/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 17:56:01 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/19 23:25:40 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void		map_size(t_scene *scene, int fd, int ret, char *f_line)
{
	int		count;
	int		res;
	(void)ret;

	count = 0;
	while (((res = get_next_line(fd, &f_line)) > 0 &&
	count < scene->len_prms) || f_line[0] == '\0')
		count++;
	while (res > 0)
	{
		if ((int)ft_strlen(f_line) > scene->line_m)
			scene->line_m = ft_strlen(f_line);
		res = get_next_line(fd, &f_line);
		scene->map_s++;
	}
	scene->map_s++;
}

void		cvt_lst_to_array(t_scene *scene_p, char *f_line, int fd, int ret)
{
	int		i;
	int		j;

	while (ret > 0 && f_line[0] == '\0')
		ret = get_next_line(fd, &f_line);
	scene_p->map_a = malloc(scene_p->map_s * sizeof(char*));
	i = -1;
	while (ret > 0)
	{
		j = -1;
		scene_p->map_a[++i] = malloc((scene_p->line_m + 1) * sizeof(char));
		if (f_line[0] == '\0')
			exit_message_failure(12);
		while (++j < scene_p->line_m)
		{
			if (j < (int)ft_strlen(f_line))
				scene_p->map_a[i][j] = f_line[j];
			else
				scene_p->map_a[i][j] = ' ';
		}
		scene_p->map_a[i][j] = '\0';
		ret = get_next_line(fd, &f_line);
	}
	if (ret == 0 && f_line[0] != '\0')
	{
		i++;
		j = -1;
		scene_p->map_a[i] = malloc((scene_p->line_m + 1) * sizeof(char));
		while (++j < scene_p->line_m)
		{
			if (j < (int)ft_strlen(f_line))
				scene_p->map_a[i][j] = f_line[j];
			else
				scene_p->map_a[i][j] = ' ';
		}
		scene_p->map_a[i][j] = '\0';
	}
}
