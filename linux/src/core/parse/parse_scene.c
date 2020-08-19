/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 17:51:10 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/19 22:25:12 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdio.h>

static int	are_params_found(t_scene *s)
{
	int		nbr;

	nbr = 0;
	nbr = s->scrn.x != 0 && s->scrn.y != 0 ? (nbr + 1) :
	nbr;
	nbr = s->tex[0].path != NULL ? nbr + 1 : nbr;
	nbr = s->tex[1].path != NULL ? nbr + 1 : nbr;
	nbr = s->tex[2].path != NULL ? nbr + 1 : nbr;
	nbr = s->tex[3].path != NULL ? nbr + 1 : nbr;
	nbr = s->tex[4].path != NULL ? nbr + 1 : nbr;
	nbr = (s->col[0].r != 300 && s->col[0].g != 300 && s->col[0].b != 300) ?
	nbr + 1 : nbr;
	nbr = (s->col[1].r != 300 && s->col[1].g != 300 && s->col[1].b != 300) ?
	nbr + 1 : nbr;
	if (nbr == 8)
		return (1);
	return (0);
}

static int	is_env_params(char c)
{
	if (c == 'R' || c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == 'S' ||
	c == 'F' || c == 'C' || c == '\0')
		return (1);
	return (0);
}

static void	cvt_player_orient(char c, t_scene *s)
{
	if (c == 'N')
	{
		s->plyr.dir.x = -1;
		s->plyr.dir.y = 0;
	}
	else if (c == 'S')
	{
		s->plyr.dir.x = 1;
		s->plyr.dir.y = 0;
	}
	else if (c == 'E')
	{
		s->plyr.dir.x = 0;
		s->plyr.dir.y = 1;
	}
	else
	{
		s->plyr.dir.x = 0;
		s->plyr.dir.y = -1;
	}
}

static void	parse_player_pos(t_scene *s)
{
	int i;
	int j;

	i = 0;
	while (i < s->map_s)
	{
		j = 0;
		while (s->map_a[i][j])
		{
			if (ft_strrchr("NSEW", s->map_a[i][j]))
			{
				s->plyr.pos.x = i;
				s->plyr.pos.y = j;
				cvt_player_orient(s->map_a[i][j], s);
				s->map_a[i][j] = '0';
			}
			if (ft_strrchr("2", s->map_a[i][j]))
				s->sprt.nbr++;
			j++;
		}
		i++;
	}
	s->plyr.pos.x += 0.5;
	s->plyr.pos.y += 0.5;
}

void		parse_scene(t_env *e, t_scene *s, char *argv[])
{
	int		ret;
	char	*f_line;

	f_line = NULL;
	s->col[0] = (t_rgb){300, 300, 300};
	s->col[1] = (t_rgb){300, 300, 300};
	e->fd_prms = open(argv[1], O_RDONLY);
	e->fd_map = open(argv[1], O_RDONLY);
	while ((ret = get_next_line(e->fd_prms, &f_line)) > 0 && !are_params_found(s))
	{
		if (!is_env_params(f_line[0]))
			exit_message_failure(2);
		parse_env_params(f_line, s);
		s->len_prms++;
		free(f_line);
	}
	if (!are_params_found(s))
		exit_message_failure(1);
	map_size(s, e->fd_map, ret, f_line);
	cvt_lst_to_array(s, f_line, e->fd_prms, ret);
	if ((!parse_map(s->map_a, s)) || (!(is_map_closed(s->map_a, s))))
		exit_message_failure(6);
	parse_player_pos(s);
}
