/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 17:53:19 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/19 11:55:53 by mvaldes          ###   ########.fr       */
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
			if (i == len -1
			|| (f_line[i + 1] < '0' || f_line[i + 1] > '9'))
				nbr++;
			i++;
		}
		i++;
	}
	return (nbr);
}

static void		cvt_screen_res(t_scene *scene_p, char *f_line)
{
	char	**str_array;
	int		nbr;

	nbr = find_nbrs(f_line);
	if (nbr != 2 || f_line[1] == '\0')
		exit_message_failure(11);
	f_line++;
	str_array = ft_split(f_line, ' ');
	if (!ft_isnum(str_array[0]) || !ft_isnum(str_array[1]))
		exit_message_failure(11);
	scene_p->scrn.x = ft_atoi(str_array[0]);
	scene_p->scrn.y = ft_atoi(str_array[1]);
	if (scene_p->scrn.x < 0 || scene_p->scrn.y < 0)
		exit_message_failure(11);
	free_prms(str_array);
}

static void		cvt_rgb(t_rgb *rgb, char *f_line)
{
	char	**str_array;
	int		b;
	int		g;
	int		r;

	f_line++;
	while (*f_line == ' ')
		f_line++;
	str_array = ft_split(f_line, ',');
	if (word_count(f_line, ',') != 3 || !ft_isnum(str_array[0]) ||
	!ft_isnum(str_array[1]) || !ft_isnum(str_array[2]))
		exit_message_failure(5);
	b = ft_atoi(str_array[2]);
	g = ft_atoi(str_array[1]);
	r = ft_atoi(str_array[0]);
	free_prms(str_array);
	if ((!((r <= 255 && r >= 0) && (g <= 255 && g >= 0) &&
	(b <= 255 && b >= 0))))
		exit_message_failure(5);
	rgb->b = b;
	rgb->g = g;
	rgb->r = r;
}

static void		cvt_text_path(char **text_path, char *f_line)
{
	while (*f_line == 'N' || *f_line == 'O' || *f_line == 'S' || *f_line == 'W'
	|| *f_line == 'E' || *f_line == 'A' || *f_line == ' ')
		f_line++;
	if (!(*text_path = ft_strdup(f_line))
	|| ft_strnstr(*text_path, "xpm", ft_strlen(*text_path)) == '\0')
		exit_message_failure(4);
}

void			parse_env_params(char *f_line, t_scene *scene_p)
{
	if (f_line[0] == 'R')
		cvt_screen_res(scene_p, f_line);
	else if (f_line[0] == 'N' && f_line[1] == 'O')
		cvt_text_path(&(scene_p->tex[0].path), f_line);
	else if (f_line[0] == 'S' && f_line[1] == 'O')
		cvt_text_path(&(scene_p->tex[1].path), f_line);
	else if (f_line[0] == 'E' && f_line[1] == 'A')
		cvt_text_path(&(scene_p->tex[2].path), f_line);
	else if (f_line[0] == 'W' && f_line[1] == 'E')
		cvt_text_path(&(scene_p->tex[3].path), f_line);
	else if (f_line[0] == 'S' && f_line[1] == ' ')
		cvt_text_path(&(scene_p->tex[4].path), f_line);
	else if (f_line[0] == 'F')
		cvt_rgb(&(scene_p->col[1]), f_line);
	else if (f_line[0] == 'C')
		cvt_rgb(&(scene_p->col[0]), f_line);
}
