/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 17:51:10 by mvaldes           #+#    #+#             */
/*   Updated: 2020/07/13 18:43:41 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	are_params_found(t_scene *scn_p)
{
	int		n_prm;

	n_prm = 0;
	n_prm = scn_p->screen.x != 0 && scn_p->screen.y != 0 ? (n_prm + 1) : n_prm;
	n_prm = scn_p->n_tex != NULL ? (n_prm + 1) : n_prm;
	n_prm = scn_p->s_tex != NULL ? (n_prm + 1) : n_prm;
	n_prm = scn_p->e_tex != NULL ? (n_prm + 1) : n_prm;
	n_prm = scn_p->w_tex != NULL ? (n_prm + 1) : n_prm;
	n_prm = scn_p->sprt_tex != NULL ? (n_prm + 1) : n_prm;
	n_prm = scn_p->flr_clr.b != 0 ? (n_prm + 1) : n_prm;
	n_prm = scn_p->cei_clr.b != 0 ? (n_prm + 1) : n_prm;
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

static int	cvt_player_orient(char c)
{
	if (c == 'N')
		return (90);
	else if (c == 'S')
		return (270);
	else if (c == 'E')
		return (0);
	else
		return (180);
}

static void	parse_player_pos(t_scene *scene_p)
{
	int i;
	int j;

	i = 0;
	ft_bzero(&scene_p->player, sizeof(scene_p->player));
	while (scene_p->map_a[i] != NULL)
	{
		j = 0;
		while (scene_p->map_a[i][j])
		{
			if (ft_strrchr("NSEW", scene_p->map_a[i][j]))
			{
				scene_p->player.pos.x = j * 64 + 64 / 2;
				scene_p->player.pos.y = i * 64 + 64 / 2;
				scene_p->player.orient =
				cvt_player_orient(scene_p->map_a[i][j]);
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
