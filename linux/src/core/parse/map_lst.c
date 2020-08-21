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

void		find_map_size(t_env *e, t_scene *s, char *argv[])
{
	int		count;
	int		res;
	char	*lline;

	count = 0;
	e->fd_map_s = open(argv[1], O_RDONLY);
	while ((res = get_next_line(e->fd_map_s, &lline) > 0))
	{
		if (count < s->len_prms)
			count++;
		else
		{
			if ((int)ft_strlen(lline) > s->line_m)
				s->line_m = ft_strlen(lline);
			if (lline[0] == '\0')
				exit_message_failure(3, e, 12, lline);
			else
				s->map_s++;
		}
		free(lline);
	}
	if (lline[0] != '\0')
		s->map_s++;
	if (lline)
		free(lline);
}

static void	put_lst_line_to_array(t_scene *scene_p, char *previous_l, int res,
int i)
{
	int j;

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

static void	put_line_to_array(t_scene *scene_p, int i, char *line)
{
	int j;

	j = -1;
	while (++j < scene_p->line_m)
	{
		if (j < (int)ft_strlen(line))
			scene_p->map_a[i][j] = line[j];
		else
			scene_p->map_a[i][j] = ' ';
	}
	scene_p->map_a[i][j] = '\0';
}

void		cvt_fle_to_array(t_env *e, t_scene *s, char *argv[])
{
	char	*line;
	int		count;
	int		res;
	int		i;

	count = 0;
	e->fd_map_a = open(argv[1], O_RDONLY);
	s->map_a = malloc(s->map_s * sizeof(char *));
	i = -1;
	while ((res = get_next_line(e->fd_map_a, &line) > 0))
	{
		if (count < s->len_prms)
			count++;
		else
		{
			s->map_a[++i] = malloc((s->line_m + 1) * sizeof(char));
			if (line[0] == '\0')
				exit_message_failure(3, e, 12, line);
			put_line_to_array(s, i, line);
		}
		free(line);
	}
	put_lst_line_to_array(s, line, res, i);
	free(line);
}
