/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 13:36:31 by mvaldes           #+#    #+#             */
/*   Updated: 2020/07/20 17:23:41 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float v_length(t_point vector)
{
	return (sqrt((vector.x * vector.x) + (vector.y * vector.y)));
}

static void	init_camera(t_scene *scene_p)
{
	ft_bzero(&(scene_p->camera.planeDir), sizeof(scene_p->camera.planeDir));
	// scene_p->camera.planeLength = scene_p->screen.x;
	// scene_p->camera.dirLength = (scene_p->camera.planeLength / 2) /
	// tan(scene_p->camera.cameraFov / 2 * (M_PI / 180));
	// scene_p->camera.dirLength = 1662;
	// scene_p->camera.angleRays = (float)scene_p->camera.cameraFov / (float)scene_p->camera.planeLength;
	scene_p->camera.cameraFov = 66;
	scene_p->camera.planeDir.x = scene_p->player.dir.y * 0.66 / 1;
	scene_p->camera.planeDir.y = (-scene_p->player.dir.x) * 0.66 / 1;
	if (scene_p->camera.planeDir.y == 0)
		scene_p->camera.planeDir.y = 0;
	if (scene_p->camera.planeDir.x == 0)
		scene_p->camera.planeDir.x = 0;
	scene_p->camera.planeLength = v_length(scene_p->camera.planeDir) * 2;
	scene_p->camera.dirLength = v_length(scene_p->player.dir);
	// scene_p->camera.cameraFov = (atan((float)(scene_p->camera.planeLength / 2) / (float)scene_p->camera.dirLength)) * 2 * (180 / M_PI);
}

void		init_scene(char **argv, t_scene *scene_p)
{
	ft_bzero(&scene_p->player, sizeof(scene_p->player));
	ft_bzero(&scene_p->camera, sizeof(scene_p->camera));
	parse_scene(scene_p, open(argv[1], O_RDONLY));
	init_camera(scene_p);
}
