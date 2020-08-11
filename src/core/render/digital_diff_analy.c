/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digital_diff_analy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 16:07:48 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/11 09:25:52 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	find_step(t_raycast *ray, t_scene *s)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_d.x = (s->plyr.pos.x - (int)ray->map.x) * ray->delta_d.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_d.x = ((int)ray->map.x + 1 - s->plyr.pos.x) * ray->delta_d.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_d.y = (s->plyr.pos.y - (int)ray->map.y) * ray->delta_d.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_d.y = ((int)ray->map.y + 1 - s->plyr.pos.y) * ray->delta_d.y;
	}
}

static void	find_wall(t_raycast *ray, t_scene *s)
{
	while (ray->wall == 0)
	{
		if (ray->side_d.x < ray->side_d.y)
		{
			ray->side_d.x += ray->delta_d.x;
			ray->map.x += (int)ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_d.y += ray->delta_d.y;
			ray->map.y += (int)ray->step.y;
			ray->side = 1;
		}
		if (s->map_a[(int)ray->map.x][(int)ray->map.y] == '1')
			ray->wall = 1;
	}
}

static void	calc_dist_to_wall(t_raycast *ray, t_scene *s)
{
	if (ray->side == 0)
		ray->wall_d = ((int)ray->map.x - s->plyr.pos.x + (1 - ray->step.x) / 2)
		/ ray->ray_dir.x;
	else
		ray->wall_d = ((int)ray->map.y - s->plyr.pos.y + (1 - ray->step.y) / 2)
		/ ray->ray_dir.y;
}

static void	dig_diff_analy(t_raycast *ray, t_scene *s)
{
	ray->map.x = (int)s->plyr.pos.x;
	ray->map.y = (int)s->plyr.pos.y;
	if (ray->ray_dir.y == 0)
		ray->delta_d.x = 0;
	else
		ray->delta_d.x = (ray->ray_dir.x == 0) ? 1 : fabs(1 / ray->ray_dir.x);
	if (ray->ray_dir.x == 0)
		ray->delta_d.y = 0;
	else
		ray->delta_d.y = (ray->ray_dir.y == 0) ? 1 : fabs(1 / ray->ray_dir.y);
	find_step(ray, s);
	find_wall(ray, s);
	calc_dist_to_wall(ray, s);
}

void		draw_env(t_scene *s, t_env *e)
{
	int			i;
	double		w;
	double		cam_x;
	t_raycast	raycast;
	t_raycast	*ray_p;

	ray_p = &raycast;
	i = 0;
	w = s->scrn.x;
	while (i < w)
	{
		ft_bzero(&raycast, sizeof(raycast));
		cam_x = ((2 * i) / (w - 1)) - 1;
		ray_p->ray_dir.x = s->plyr.dir.x + s->cam.pln.x * cam_x;
		ray_p->ray_dir.y = s->plyr.dir.y + s->cam.pln.y * cam_x;
		dig_diff_analy(&raycast, s);
		draw_vert_line(s, e, ray_p, i);
		s->cam.z_buffer[i] = ray_p->wall_d;
		i++;
	}
	draw_sprites(s, e, &s->sprt);
	mlx_put_image_to_window(e->mlx_ptr, e->mlx_win, e->mlx_img.addr, 0, 0);
}
