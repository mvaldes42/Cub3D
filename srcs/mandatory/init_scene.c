/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 13:36:31 by mvaldes           #+#    #+#             */
/*   Updated: 2020/07/13 18:44:02 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_camera(t_scene *scene_ptr)
{
	// scene_ptr->camera.dirLength = (scene_ptr->camera.planeLength / 2) /
	// tan(scene_ptr->camera.cameraFov / 2 * (M_PI / 180));
	// scene_ptr->camera.cameraFov = 60;

	scene_ptr->camera.planeLength = scene_ptr->screen.x;
	scene_ptr->camera.dirLength = 1662;
	scene_ptr->camera.cameraFov = (atan((float)(scene_ptr->camera.planeLength / 2) / (float)scene_ptr->camera.dirLength)) * 2 * (180 / M_PI);
	scene_ptr->camera.angleRays = (float)scene_ptr->camera.cameraFov / (float)scene_ptr->camera.planeLength;

	scene_ptr->camera.planeCenter.x = scene_ptr->screen.x / 2;
	scene_ptr->camera.planeCenter.y = scene_ptr->screen.y / 2;
}

void		init_scene(char **argv, t_scene *scene_ptr)
{
	parse_scene(scene_ptr, open(argv[1], O_RDONLY));
	init_camera(scene_ptr);
}
