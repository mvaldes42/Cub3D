/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 17:53:19 by mvaldes           #+#    #+#             */
/*   Updated: 2020/04/29 18:00:31 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_screen	get_screen_res(char *f_line)
{
	t_screen	screen;
	char		**str_array;

	str_array = (char **)malloc(sizeof(char *) * 3 + 1);
	str_array = ft_split(f_line, ' ');
	screen.x = ft_atoi(str_array[1]);
	screen.y = ft_atoi(str_array[2]);
	free(str_array);
	return (screen);
}

static int		word_count(const char *s, char c)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static t_rgb	get_rgb(char *f_line)
{
	t_rgb	rgb;
	char	**str_array;
	int		b;
	int		g;
	int		r;

	bzero(&rgb, sizeof(rgb));
	str_array = (char **)malloc(sizeof(char *) * word_count(f_line, ',') + 1);
	ft_memmove(f_line, f_line + 2, ft_strlen(f_line) - 2 + 1);
	str_array = ft_split(f_line, ',');
	b = ft_atoi(str_array[1]);
	g = ft_atoi(str_array[2]);
	r = ft_atoi(str_array[3]);
	if ((!((b <= 255 && b >= 0) && (g <= 255 && b >= 0) &&
	(r <= 255 && b >= 0))) || (word_count(f_line, ',') != 3))
	{
		g_error = 5;
		exit_message_failure();
	}
	rgb.b = b;
	rgb.g = g;
	rgb.r = r;
	free(str_array);
	return (rgb);
}

static char		*get_text(char *f_line)
{
	char *tmp;

	if (!(tmp = ft_strchr(f_line, '.'))
	|| ft_strnstr(tmp, "xpm", ft_strlen(tmp)) == '\0')
	{
		g_error = 4;
		exit_message_failure();
	}
	return (tmp);
}

t_scene			parse_env_params(char *f_line, t_scene scn)
{
	scn.screen = f_line[0] == 'R' ? get_screen_res(f_line) : scn.screen;
	scn.n_tex = f_line[0] == 'N' && f_line[1] == 'O' ? get_text(f_line)
	: scn.n_tex;
	scn.s_tex = f_line[0] == 'S' && f_line[1] == 'O' ? get_text(f_line)
	: scn.s_tex;
	scn.e_tex = f_line[0] == 'E' && f_line[1] == 'A' ? get_text(f_line)
	: scn.e_tex;
	scn.w_tex = f_line[0] == 'W' && f_line[1] == 'E' ? get_text(f_line)
	: scn.w_tex;
	scn.sprt_tex = f_line[0] == 'S' && f_line[1] == ' ' ? get_text(f_line)
	: scn.sprt_tex;
	scn.flr_clr = f_line[0] == 'F' ? get_rgb(f_line) : scn.flr_clr;
	scn.cei_clr = f_line[0] == 'C' ? get_rgb(f_line) : scn.cei_clr;
	return (scn);
}
