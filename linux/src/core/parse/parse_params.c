/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 17:53:19 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/20 15:36:14 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int		find_nbrs(char *f_line)
{
	int		i;
	int		nbr;
	int		len;

	len = 0;
	while (f_line[len])
		len++;
	i = 1;
	nbr = 0;
	while (i < len && f_line[i] == ' ')
		i++;
	while (i < len)
	{
		while ((f_line[i] >= '0' && f_line[i] <= '9'))
		{
			if (i == len - 1
			|| (f_line[i + 1] < '0' || f_line[i + 1] > '9'))
				nbr++;
			i++;
		}
		i++;
	}
	return (nbr);
}

static int	cvt_screen_res(t_scene *scene_p, char *line)
{
	char	**str_array;
	int		nbr;

	nbr = find_nbrs(line);
	if (nbr != 2 || line[1] == '\0')
		return (0);
	line++;
	str_array = ft_split(line, ' ');
	if (!ft_isnum(str_array[0]) || !ft_isnum(str_array[1]))
	{
		free_prms(str_array);
		return (0);
	}
	scene_p->scrn.x = ft_atoi(str_array[0]);
	scene_p->scrn.y = ft_atoi(str_array[1]);
	if (scene_p->scrn.x < 0 || scene_p->scrn.y < 0)
	{
		free_prms(str_array);
		return (0);
	}
	free_prms(str_array);
	return (1);
}

static int		cvt_rgb(t_rgb *rgb, char *line)
{
	char	**str_array;
	int		b;
	int		g;
	int		r;

	line++;
	while (*line == ' ')
		line++;
	str_array = ft_split(line, ',');
	if (word_count(line, ',') != 3 || !ft_isnum(str_array[0]) ||
	!ft_isnum(str_array[1]) || !ft_isnum(str_array[2]))
	{
		free_prms(str_array);
		return(0);
	}
	b = ft_atoi(str_array[2]);
	g = ft_atoi(str_array[1]);
	r = ft_atoi(str_array[0]);
	free_prms(str_array);
	if ((!((r <= 255 && r >= 0) && (g <= 255 && g >= 0) &&
	(b <= 255 && b >= 0))))
		return (0);
	rgb->b = b;
	rgb->g = g;
	rgb->r = r;
	return (1);
}

static int	cvt_text_path(char **text_path, char *line)
{
	while (*line == 'N' || *line == 'O' || *line == 'S' || *line == 'W'
	|| *line == 'E' || *line == 'A' || *line == ' ')
		line++;
	if (!(*text_path = ft_strdup(line))
	|| ft_strnstr(*text_path, "xpm", ft_strlen(*text_path)) == '\0')
		return (0);
	return (1);
}

void			parse_env_params(t_env *e, char *f_line, t_scene *scene_p)
{
	if (f_line[0] == 'R')
		if (!cvt_screen_res(scene_p, f_line))
			exit_message_failure(3, e, 11, f_line);
	if (f_line[0] == 'N' && f_line[1] == 'O')
		if (!cvt_text_path(&(scene_p->tex[0].path), f_line))
			exit_message_failure(3, e, 4, f_line);
	if (f_line[0] == 'S' && f_line[1] == 'O')
		if (!cvt_text_path(&(scene_p->tex[1].path), f_line))
			exit_message_failure(3, e, 4, f_line);
	if (f_line[0] == 'E' && f_line[1] == 'A')
		if (!cvt_text_path(&(scene_p->tex[2].path), f_line))
			exit_message_failure(3, e, 4, f_line);
	if (f_line[0] == 'W' && f_line[1] == 'E')
		if (!cvt_text_path(&(scene_p->tex[3].path), f_line))
			exit_message_failure(3, e, 4, f_line);
	if (f_line[0] == 'S' && f_line[1] == ' ')
		if (!cvt_text_path(&(scene_p->tex[4].path), f_line))
			exit_message_failure(3, e, 4, f_line);
	if (f_line[0] == 'F')
		if (!cvt_rgb(&(scene_p->col[1]), f_line))
			exit_message_failure(3, e, 5, f_line);
	if (f_line[0] == 'C')
		if (!cvt_rgb(&(scene_p->col[0]), f_line))
			exit_message_failure(3, e, 5, f_line);
}
