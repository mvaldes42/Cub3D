/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digitalDifAnaly.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 16:07:48 by mvaldes           #+#    #+#             */
/*   Updated: 2020/07/21 15:17:00 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	find_step(t_raycast *raycast_p, t_scene *scene_p)
{
	if (raycast_p->ray_dir.x < 0)
	{
	raycast_p->step.x = -1;
	raycast_p->side_dist.x = (scene_p->player.pos.x - (int)raycast_p->map.x) *
	raycast_p->delta_dist.x;
	}
	else
	{
	raycast_p->step.x = 1;
	raycast_p->side_dist.x = ((int)raycast_p->map.x + 1 - scene_p->player.pos.x) *
	raycast_p->delta_dist.x;
	}
	if (raycast_p->ray_dir.y < 0)
	{
	raycast_p->step.y = -1;
	raycast_p->side_dist.y = (scene_p->player.pos.y - (int)raycast_p->map.y) *
	raycast_p->delta_dist.y;
	}
	else
	{
	raycast_p->step.y = 1;
	raycast_p->side_dist.y = ((int)raycast_p->map.y + 1 - scene_p->player.pos.y) *
	raycast_p->delta_dist.y;
	}
}

static void find_wall(t_raycast *raycast_p, t_scene *scene_p)
{
	while (raycast_p->wall == 0)
	{
		// printf("side_dist.x : %f / side_dist.y : %f / ", raycast_p->side_dist.x, raycast_p->side_dist.y);
		// printf("delta_dist.x : %f / delta_dist.y : %f / ",raycast_p->delta_dist.x, raycast_p->delta_dist.y);
		if (raycast_p->side_dist.x < raycast_p->side_dist.y)
		{
			raycast_p->side_dist.x += raycast_p->delta_dist.x;
			raycast_p->map.x += (int)raycast_p->step.x;
			raycast_p->side = 0;
		}
		else
		{
			raycast_p->side_dist.y += raycast_p->delta_dist.y;
			raycast_p->map.y += (int)raycast_p->step.y;
			raycast_p->side = 1;
		}
		if (scene_p->map_a[(int)raycast_p->map.x][(int)raycast_p->map.y] == '1')
		{
			raycast_p->wall = 1;
			printf("wall x : %d, wall y: %d\n\n", (int)raycast_p->map.x, (int)raycast_p->map.y);
		}
	}
}

static void calc_dist_to_wall(t_raycast *raycast_p, t_scene *scene)
{
	if (raycast_p->side == 0)
		raycast_p->wall_dist = ((int)raycast_p->map.x - scene->player.pos.x +
		(1 - raycast_p->step.x) / 2) / raycast_p->ray_dir.x;
	else
		raycast_p->wall_dist = ((int)raycast_p->map.y - scene->player.pos.y +
		(1 - raycast_p->step.y) / 2) / raycast_p->ray_dir.y;
}

static void dig_diff_analy(t_raycast *raycast_p, t_scene *scene_p)
{
	raycast_p->map.x = (int)scene_p->player.pos.x;
	raycast_p->map.y = (int)scene_p->player.pos.y;
	raycast_p->delta_dist.x = (raycast_p->ray_dir.y == 0) ? 0 : ((raycast_p->ray_dir.x == 0) ? 1 : fabs(1 / raycast_p->ray_dir.x));
	raycast_p->delta_dist.y = (raycast_p->ray_dir.x == 0) ? 0 : ((raycast_p->ray_dir.y == 0) ? 1 : fabs(1 / raycast_p->ray_dir.y));
	find_step(raycast_p, scene_p);
	find_wall(raycast_p, scene_p);
	calc_dist_to_wall(raycast_p, scene_p);
}

void	cast_rays_to_wall(t_scene *scene_p)
{
	int i;
	double w;
	double camera_x;
	t_raycast raycast;
	t_raycast *raycast_p;

	raycast_p = &raycast;
	i = 0;
	w = scene_p->screen.x;
	while(i < w)
	{
		ft_bzero(&raycast, sizeof(raycast));
		camera_x = ((2 * i) / (w - 1)) - 1;
		raycast_p->ray_dir.x = scene_p->player.dir.x + scene_p->camera.planeDir.x * camera_x;
		raycast_p->ray_dir.y = scene_p->player.dir.y + scene_p->camera.planeDir.y * camera_x;
		dig_diff_analy(&raycast, scene_p);
		printf("i : %d & ray_dir.x : %f & ray_dir.y : %f & camera_x: %f & dist_wall : %f\n", i, raycast_p->ray_dir.x, raycast_p->ray_dir.y, camera_x, raycast_p->wall_dist);
		i++;
	}
	printf("scene_p->player.pos.x : %f\n", scene_p->player.pos.x);
	printf("scene_p->player.pos.y : %f\n", scene_p->player.pos.y);
	printf("scene_ptr->player.dir.x : %f\n", scene_p->player.dir.x);
	printf("scene_ptr->player.dir.y : %f\n", scene_p->player.dir.y);
	printf("scene_ptr->camera.planeDir.x : %f\n", scene_p->camera.planeDir.x);
	printf("scene_ptr->camera.planeDir.y : %f\n", scene_p->camera.planeDir.y);
	printf("scene_ptr->camera.planeLength : %f\n", scene_p->camera.planeLength);
	printf("scene_ptr->camera.dirLength  : %f\n", scene_p->camera.dirLength);
}



