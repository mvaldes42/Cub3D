/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digitalDifAnaly.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 16:07:48 by mvaldes           #+#    #+#             */
/*   Updated: 2020/07/21 16:33:13 by mvaldes          ###   ########.fr       */
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
			printf("wall x : %d, wall y: %d\n\n", ((int)raycast_p->map.x), ((int)raycast_p->map.y));
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

// static char *decToHexa(int n)
// {
//     char hexaDeciNum[2];

//     int i = 0;
//     while (n != 0)
//     {
//         int temp = 0;
//         temp = n % 16;
//         if (temp < 10)
//         {
//             hexaDeciNum[i] = (char) (temp + 48);
//             i++;
//         }
//         else
//         {
//             hexaDeciNum[i] = (char) (temp + 55);
//             i++;
//         }
//         n = n / 16;
//     }
//     char *hexCode = "";
//     if (i == 2)
//     {
//         hexCode += hexaDeciNum[0];
//         hexCode += hexaDeciNum[1];
//     }
//     else if (i == 1)
//     {
//         hexCode = "0";
//         hexCode += hexaDeciNum[0];
//     }
//     else if (i == 0)
//         hexCode = "00";
//     return hexCode;
// }

// static char *from_rgb_to_hex(int R, int G, int B)
// {
// 	if ((R >= 0 && R <= 255) && (G >= 0 && G <= 255) && (B >= 0 && B <= 255))
// 	{
// 		char *hexCode = "#";
// 		hexCode += strcat(hexCode, decToHexa(R));
// 		hexCode += strcat(hexCode, decToHexa(G));
// 		hexCode += strcat(hexCode, decToHexa(B));
// 	}
// }

static void	draw_walls(t_scene *scene_p, t_env *env_p, t_raycast *raycast_p, int i)
{
	//Calculate height of line to draw on screen
	int lineHeight;
	int h = scene_p->screen.y;

	lineHeight = (int)(h / raycast_p->wall_dist);

	//calculate lowest and highest pixel to fill in current stripe
	int drawStart = -lineHeight / 2 + h / 2;
	if(drawStart < 0)drawStart = 0;
	int drawEnd = lineHeight / 2 + h / 2;
	if(drawEnd >= h)drawEnd = h - 1;

	//choose wall color
	// t_rgb color;
	// ft_bzero(&color, sizeof(color));
	// switch(scene_p->map_a[(int)raycast_p->map.x][(int)raycast_p->map.y])
	// {
	// 	case 1:  color.r = 255;  break; //red
	// 	case 2:  color.g = 255;  break; //green
	// 	case 3:  color.b = 255;   break; //blue
	// 	case 4:  color.r = 255; color.g = 255; color.b = 255;  break; //white
	// 	default: color.r = 255; color.g = 255; break; //yellow
	// }
	// //give x and y sides different brightness
	// if (raycast_p->side == 1)
	// {
	// 	color.r = (255 - color.r) / 2;
	// 	color.g = (255 - color.g) / 2;
	// 	color.b = (255 - color.b) / 2;
	// }
	int j = drawStart;
	while (j < drawEnd)
	{
		mlx_pixel_put(env_p->mlx_ptr, env_p->mlx_win, i, j, 0xFFCCCC);
		j++;
	}
}

void	cast_rays_to_wall(t_scene *scene_p, t_env *env_p)
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
		draw_walls(scene_p, env_p, raycast_p, i);
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



