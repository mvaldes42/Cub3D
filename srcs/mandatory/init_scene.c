/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 13:36:31 by mvaldes           #+#    #+#             */
/*   Updated: 2020/07/22 17:13:28 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	v_length(t_point vector)
{
	return (sqrt((vector.x * vector.x) + (vector.y * vector.y)));
}

static void		init_camera(t_scene *scene_p)
{
	ft_bzero(&(scene_p->cam.pln_dir), sizeof(scene_p->cam.pln_dir));
	scene_p->cam.cam_fov = 66;
	scene_p->cam.pln_dir.x = scene_p->player.dir.y * 0.66 / 1;
	scene_p->cam.pln_dir.y = (-scene_p->player.dir.x) * 0.66 / 1;
	if (scene_p->cam.pln_dir.y == 0)
		scene_p->cam.pln_dir.y = 0;
	if (scene_p->cam.pln_dir.x == 0)
		scene_p->cam.pln_dir.x = 0;
	scene_p->cam.pln_len = v_length(scene_p->cam.pln_dir) * 2;
	scene_p->cam.dir_len = v_length(scene_p->player.dir);
}

void			init_scene(char **argv, t_scene *scene_p)
{
	ft_bzero(&scene_p->player, sizeof(scene_p->player));
	ft_bzero(&scene_p->cam, sizeof(scene_p->cam));
	parse_scene(scene_p, open(argv[1], O_RDONLY));
	init_camera(scene_p);
}

/*
**	scene_p->cam.pln_len = scene_p->screen.x;
**	scene_p->cam.dir_len = (scene_p->cam.pln_len / 2) /
**	tan(scene_p->cam.cam_fov / 2 * (M_PI / 180));
**	scene_p->cam.dir_len = 1662;
**	scene_p->cam.angleRays = (float)scene_p->cam.cam_fov /
**	(float)scene_p->cam.pln_len;
**	scene_p->cam.cam_fov = (atan((float)(scene_p->cam.pln_len / 2) /
**	(float)scene_p->cam.dir_len)) * 2 * (180 / M_PI);
*/
