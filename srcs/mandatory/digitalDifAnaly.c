/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digitalDifAnaly.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 16:07:48 by mvaldes           #+#    #+#             */
/*   Updated: 2020/07/13 18:50:24 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static int is_wall_here(t_point A, t_scene *scene_p)
{
	if (scene_p->map_a[(int)floor(A.y / 64)][(int)floor(A.x / 64)] == '1')
		return (1);
	else
		return (0);
}

static t_point	find_wall(t_point current_inter, int x_delta, int y_delta, t_scene *scene_p)
{
	if (!is_wall_here(current_inter, scene_p)) {
		current_inter.x = current_inter.x + x_delta;
		current_inter.y = current_inter.y + y_delta;
		return find_wall(current_inter, x_delta, y_delta, scene_p);
	}
	return (current_inter);
}

static t_point	find_horizontal_inter(t_scene *scene_p)
{
	t_point first_inter;
	t_point current_inter;
	int		x_delta;
	int		y_delta;

	if (scene_p->player.orient < 180)
	{
		first_inter.y = (double)(floor(scene_p->player.pos.y / 64) - 1) * 64;
		y_delta = -64;
	}
	else
	{
		first_inter.y = (double)(floor(scene_p->player.pos.y / 64) + 64) * 64;
		y_delta  = 64;
	}
	first_inter.x = scene_p->player.pos.x +(scene_p->player.pos.y -
	first_inter.y) / tan(scene_p->player.orient * (M_PI / 180));
	x_delta = 64 / tan(60 * (M_PI / 180));
	if (!is_wall_here(first_inter, scene_p))
	{
		current_inter.x = first_inter.x + x_delta;
		current_inter.y = first_inter.y + y_delta;
		return (find_wall(current_inter, x_delta, y_delta, scene_p));
	}
	return (first_inter);
}

// static void	find_vertical_inter(t_scene *scene_p)
// {

// }

void	calc_closest_wall(t_scene *scene_p)
{
	t_point horizontal_inter;
	t_point vertical_inter;

	horizontal_inter = find_horizontal_inter(scene_p);
}
