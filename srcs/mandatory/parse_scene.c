/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 17:51:10 by mvaldes           #+#    #+#             */
/*   Updated: 2020/07/28 19:05:13 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	are_params_found(t_scene *scene_p)
{
	int		n_prm;

	n_prm = 0;
	n_prm = scene_p->screen.x != 0 && scene_p->screen.y != 0 ? (n_prm + 1) :
	n_prm;
	n_prm = scene_p->n_tex != NULL ? (n_prm + 1) : n_prm;
	n_prm = scene_p->s_tex != NULL ? (n_prm + 1) : n_prm;
	n_prm = scene_p->e_tex != NULL ? (n_prm + 1) : n_prm;
	n_prm = scene_p->w_tex != NULL ? (n_prm + 1) : n_prm;
	n_prm = scene_p->sprt_tex != NULL ? (n_prm + 1) : n_prm;
	n_prm = scene_p->flr_clr.b != 0 ? (n_prm + 1) : n_prm;
	n_prm = scene_p->cei_clr.b != 0 ? (n_prm + 1) : n_prm;
	if (n_prm == 8)
		return (1);
	g_error = 1;
	return (0);
}

static int	is_env_params(char c)
{
	if (c == 'R' || c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == 'S' ||
	c == 'F' || c == 'C' || c == '\0')
		return (1);
	g_error = 2;
	return (0);
}

static void	cvt_player_orient(char c, t_scene *scene_p)
{
	ft_bzero(&scene_p->player.dir, sizeof(scene_p->player.dir));
	if (c == 'N')
	{
		scene_p->player.dir.x = -1;
		scene_p->player.dir.y = 0;
	}
	else if (c == 'S')
	{
		scene_p->player.dir.x = 1;
		scene_p->player.dir.y = 0;
	}
	else if (c == 'E')
	{
		scene_p->player.dir.x = 0;
		scene_p->player.dir.y = 1;
	}
	else
	{
		scene_p->player.dir.x = 0;
		scene_p->player.dir.y = -1;
	}
}

static void	parse_player_pos(t_scene *scene_p)
{
	int i;
	int j;

	i = 0;
	ft_bzero(&scene_p->player.pos, sizeof(scene_p->player.pos));
	while (scene_p->map_a[i] != NULL)
	{
		j = 0;
		while (scene_p->map_a[i][j])
		{
			if (ft_strrchr("NSEW", scene_p->map_a[i][j]))
			{
				scene_p->player.pos.x = i;
				scene_p->player.pos.y = j;
				cvt_player_orient(scene_p->map_a[i][j], scene_p);
				scene_p->map_a[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

void		parse_scene(t_scene *scene_p, int fd)
{
	int		ret;
	char	*f_line;

	f_line = NULL;
	while ((ret = get_next_line(fd, &f_line)) > 0 && !are_params_found(scene_p))
	{
		if (!is_env_params(f_line[0]))
			exit_message_failure();
		parse_env_params(f_line, scene_p);
	}
	if (!are_params_found(scene_p))
		exit_message_failure();
	cvt_lst_to_array(scene_p, f_line, fd, ret);
	if ((!parse_map(scene_p->map_a)) || (!(is_map_closed(scene_p->map_a))))
		exit_message_failure();
	parse_player_pos(scene_p);
	free(f_line);
}
