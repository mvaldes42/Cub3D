/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 17:51:10 by mvaldes           #+#    #+#             */
/*   Updated: 2020/04/29 19:00:56 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	are_params_found(t_scene scene)
{
	int		n_prm;

	n_prm = 0;
	n_prm = scene.screen.x != 0 && scene.screen.y != 0 ? (n_prm + 1) : n_prm;
	n_prm = scene.n_tex != NULL ? (n_prm + 1) : n_prm;
	n_prm = scene.s_tex != NULL ? (n_prm + 1) : n_prm;
	n_prm = scene.e_tex != NULL ? (n_prm + 1) : n_prm;
	n_prm = scene.w_tex != NULL ? (n_prm + 1) : n_prm;
	n_prm = scene.sprt_tex != NULL ? (n_prm + 1) : n_prm;
	n_prm = scene.flr_clr.b != 0 ? (n_prm + 1) : n_prm;
	n_prm = scene.cei_clr.b != 0 ? (n_prm + 1) : n_prm;
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

static t_player	parse_player_pos(t_scene scene)
{
	int i;
	int j;

	i = 0;
	ft_bzero(&scene.player, sizeof(scene.player));
	while (scene.map_a[i] != NULL)
	{
		j = 0;
		while (scene.map_a[i][j])
		{
			if (ft_strrchr("NSEW", scene.map_a[i][j]))
			{
				scene.player.x = j;
				scene.player.y = i;
				scene.player.orientation = scene.map_a[i][j];
			}
			j++;
		}
		i++;
	}
	return (scene.player);
}

t_scene		parse_scene(t_scene scene, int fd)
{
	int		ret;
	char	*f_line;

	f_line = NULL;
	while ((ret = get_next_line(fd, &f_line)) > 0 && !are_params_found(scene))
	{
		if (!is_env_params(f_line[0]))
			exit_message_failure();
		scene = parse_env_params(f_line, scene);
	}
	if (!are_params_found(scene))
		exit_message_failure();
	scene.map_a = convert_lst_to_array(create_map_lst(scene, f_line, fd, ret));
	if ((!parse_map(scene.map_a)) || (!(is_map_closed(scene.map_a))))
		exit_message_failure();
	scene.player = parse_player_pos(scene);
	free(f_line);
	return (scene);
}
