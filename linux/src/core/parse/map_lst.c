/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 17:56:01 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/20 15:44:56 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void		map_size(t_scene *scene, int fd)
{
	int		count;
	int		res;
	char	*lline;
	char	*mline;

	lline = NULL;
	mline = NULL;
	count = 0;
	while (((res = get_next_line(fd, &lline)) > 0 &&
	count < scene->len_prms) || lline[0] == '\0')
	{
		count++;
		free(lline);
	}
	free(lline);
	while ((res == get_next_line(fd, &mline)) > 0)
	{
		if ((int)ft_strlen(mline) > scene->line_m)
			scene->line_m = ft_strlen(mline);
		scene->map_s++;
		free(mline);
	}
	free(mline);
	scene->map_s += 2;
}

void		lline_to_array(t_scene *scene_p, char *previous_l, int res, int i)
{
	int		j;

	i++;
	if (res == 0 && previous_l[0] != '\0')
	{
		j = -1;
		scene_p->map_a[i] = malloc((scene_p->line_m + 1) * sizeof(char));
		while (++j < scene_p->line_m)
		{
			if (j < (int)ft_strlen(previous_l))
				scene_p->map_a[i][j] = previous_l[j];
			else
				scene_p->map_a[i][j] = ' ';
		}
		scene_p->map_a[i][j] = '\0';
	}
}

void		cvt_lst_to_array(t_scene *scene_p, int fd)
{
	char	*line;
	int		count;
	int		res;
	int		i;
	int		j;

	count = 0;
	res = 0;
	line = NULL;
	scene_p->map_a = malloc(scene_p->map_s * sizeof(char*));
	i = -1;
	while ((res = get_next_line(fd, &line) > 0))
	{
		if (count < scene_p->len_prms)
			count++;
		else
		{
			j = -1;
			scene_p->map_a[++i] = malloc((scene_p->line_m + 1) * sizeof(char));
			if (line[0] == '\0')
				exit_message_failure(12);
			while (++j < scene_p->line_m)
			{
				if (j < (int)ft_strlen(line))					
					scene_p->map_a[i][j] = line[j];
				else
					scene_p->map_a[i][j] = ' ';
			}
			scene_p->map_a[i][j] = '\0';
		}
		free(line);
	}
	lline_to_array(scene_p, line, res, i);
	free(line);
}
