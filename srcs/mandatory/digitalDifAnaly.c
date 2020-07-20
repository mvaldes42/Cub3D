/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digitalDifAnaly.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 16:07:48 by mvaldes           #+#    #+#             */
/*   Updated: 2020/07/20 13:47:45 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static int is_wall_here(t_point A, t_scene *scene_p)
// {
// 	printf("y: %d, x: %d -> %c\n",(int)(floor(A.y / 64)), (int)(floor(A.x / 64)), scene_p->map_a[(int)(floor(A.y / 64))][(int)(floor(A.x / 64))]);
// 	// A.y = A.y < 0 ? 0 : A.y;
// 	// A.x = A.x < 0 ? 0 : A.x;
// 	if (scene_p->map_a[(int)(floor(A.y / 64))][(int)(floor(A.x / 64))] == '1')
// 		return (1);
// 	else
// 		return (0);
// }

// static t_point	find_wall(t_point current_inter, int x_delta, int y_delta, t_scene *scene_p)
// {
// 	if (!is_wall_here(current_inter, scene_p)) {
// 		current_inter.x = current_inter.x + x_delta;
// 		current_inter.y = current_inter.y + y_delta;
// 		return find_wall(current_inter, x_delta, y_delta, scene_p);
// 	}
// 	return (current_inter);
// }

// static double dist_btw_two_points(t_point point_a, t_point point_b)
// {
// 	return (sqrt( ((point_a.x - point_a.y) * (point_a.x - point_a.y)) +
// 	((point_b.x - point_b.y) * (point_b.x - point_b.y))));
// }

void	cast_rays_to_wall(t_scene *scene_p)
{
	int i;
	double width;

	i = 0;
	width = scene_p->screen.x;
	while (i < width)
	{
		double camera_x = 2 * i / width - 1;
		double ray_dir_x = scene_p->player.dir.x + scene_p->camera.planeDir.x * camera_x;
		double ray_dir_y = scene_p->player.dir.y + scene_p->camera.planeDir.y * camera_x;
		printf("i : %d & RayDirX : %f & RayDirY : %f\n", i, ray_dir_x, ray_dir_y);
		i++;
	}
	printf("scene_ptr->player.dir.x : %f\n", scene_p->player.dir.x);
	printf("scene_ptr->player.dir.y : %f\n", scene_p->player.dir.y);
	printf("scene_ptr->camera.planeDir.x : %f\n", scene_p->camera.planeDir.x);
	printf("scene_ptr->camera.planeDir.y : %f\n", scene_p->camera.planeDir.y);
	printf("scene_ptr->camera.planeLength : %f\n", scene_p->camera.planeLength);
	printf("scene_ptr->camera.dirLength  : %f\n", scene_p->camera.dirLength);
}



