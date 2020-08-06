/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digital_diff_analy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 16:07:48 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/06 21:38:14 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void		find_step(t_raycast *ray_p, t_scene *scene_p)
{
	if (ray_p->ray_dir.x < 0)
	{
		ray_p->step.x = -1;
		ray_p->side_d.x = (scene_p->player.pos.x - (int)ray_p->map.x) *
		ray_p->delta_d.x;
	}
	else
	{
		ray_p->step.x = 1;
		ray_p->side_d.x = ((int)ray_p->map.x + 1 - scene_p->player.pos.x) *
		ray_p->delta_d.x;
	}
	if (ray_p->ray_dir.y < 0)
	{
		ray_p->step.y = -1;
		ray_p->side_d.y = (scene_p->player.pos.y - (int)ray_p->map.y) *
		ray_p->delta_d.y;
	}
	else
	{
		ray_p->step.y = 1;
		ray_p->side_d.y = ((int)ray_p->map.y + 1 - scene_p->player.pos.y) *
		ray_p->delta_d.y;
	}
}

static void		find_wall(t_raycast *ray_p, t_scene *scene_p)
{
	while (ray_p->wall == 0)
	{
		if (ray_p->side_d.x < ray_p->side_d.y)
		{
			ray_p->side_d.x += ray_p->delta_d.x;
			ray_p->map.x += (int)ray_p->step.x;
			ray_p->side = 0;
		}
		else
		{
			ray_p->side_d.y += ray_p->delta_d.y;
			ray_p->map.y += (int)ray_p->step.y;
			ray_p->side = 1;
		}
		if (scene_p->map_a[(int)ray_p->map.x][(int)ray_p->map.y] == '1')
			ray_p->wall = 1;
	}
}

static void		calc_dist_to_wall(t_raycast *ray_p, t_scene *scene)
{
	if (ray_p->side == 0)
		ray_p->wall_d = ((int)ray_p->map.x - scene->player.pos.x +
		(1 - ray_p->step.x) / 2) / ray_p->ray_dir.x;
	else
		ray_p->wall_d = ((int)ray_p->map.y - scene->player.pos.y +
		(1 - ray_p->step.y) / 2) / ray_p->ray_dir.y;
}

static void		dig_diff_analy(t_raycast *ray_p, t_scene *s_p)
{
	ray_p->map.x = (int)s_p->player.pos.x;
	ray_p->map.y = (int)s_p->player.pos.y;
	if (ray_p->ray_dir.y == 0)
		ray_p->delta_d.x = 0;
	else
		ray_p->delta_d.x = (ray_p->ray_dir.x == 0) ? 1 :
		fabs(1 / ray_p->ray_dir.x);
	if (ray_p->ray_dir.x == 0)
		ray_p->delta_d.y = 0;
	else
		ray_p->delta_d.y = (ray_p->ray_dir.y == 0) ? 1 :
		fabs(1 / ray_p->ray_dir.y);
	find_step(ray_p, s_p);
	find_wall(ray_p, s_p);
	calc_dist_to_wall(ray_p, s_p);
}

void			draw_env(t_scene *s_p, t_env *e)
{
	int			i;
	double		w;
	double		cam_x;
	t_raycast	raycast;
	t_raycast	*ray_p;

	ray_p = &raycast;
	i = 0;
	w = s_p->screen.x;
	while (i < w)
	{
		ft_bzero(&raycast, sizeof(raycast));
		cam_x = ((2 * i) / (w - 1)) - 1;
		ray_p->ray_dir.x = s_p->player.dir.x + s_p->cam.pln_dir.x * cam_x;
		ray_p->ray_dir.y = s_p->player.dir.y + s_p->cam.pln_dir.y * cam_x;
		dig_diff_analy(&raycast, s_p);
		draw_vert_line(s_p, e, ray_p, i);
		i++;
	}
	mlx_put_image_to_window(e->mlx_ptr, e->mlx_win, e->mlx_img.addr, 0, 0);
}
/*
**	printf("scene_p->player.pos.x : %f\n", scene_p->player.pos.x);
**	printf("scene_p->player.pos.y : %f\n", scene_p->player.pos.y);
**	printf("scene_ptr->player.dir.x : %f\n", scene_p->player.dir.x);
**	printf("scene_ptr->player.dir.y : %f\n", scene_p->player.dir.y);
**	printf("scene_ptr->cam.pln_dir.x : %f\n", scene_p->cam.pln_dir.x);
**	printf("scene_ptr->cam.pln_dir.y : %f\n", scene_p->cam.pln_dir.y);
**	printf("scene_ptr->cam.pln_len : %f\n", scene_p->cam.pln_len);
**	printf("scene_ptr->cam.dir_len  : %f\n", scene_p->cam.dir_len);
*/
