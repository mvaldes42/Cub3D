/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 16:22:32 by mvaldes           #+#    #+#             */
/*   Updated: 2020/07/28 16:44:26 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate(t_scene *s, int f)
{
	double r_speed;
	double old_dir_x;
	double old_plane_x;

	r_speed = 0.10;
	old_dir_x = s->player.dir.x;
	s->player.dir.x = s->player.dir.x * cos(f * r_speed)
	- s->player.dir.y * sin(f * r_speed);
	s->player.dir.y = old_dir_x * sin(f * r_speed)
	+ s->player.dir.y * cos(f * r_speed);
	old_plane_x = s->cam.pln_dir.x;
	s->cam.pln_dir.x = s->cam.pln_dir.x * cos(f * r_speed)
	- s->cam.pln_dir.y * sin(f * r_speed);
	s->cam.pln_dir.y = old_plane_x * sin(f * r_speed)
	+ s->cam.pln_dir.y * cos(f * r_speed);
}

void	move(t_scene *s, char f)
{
	double m_speed;

	m_speed = 0.5;
	if (f == 'f')
	{
		if (s->map_a[(int)(s->player.pos.x + s->player.dir.x * m_speed)]
		[(int)(s->player.pos.y)] == '0')
			s->player.pos.x += s->player.dir.x * m_speed;
		if (s->map_a[(int)(s->player.pos.x)]
		[(int)(s->player.pos.y + s->player.dir.y * m_speed)] == '0')
			s->player.pos.y += s->player.dir.y * m_speed;
	}
	else if (f == 'b')
	{
		if (s->map_a[(int)(s->player.pos.x - s->player.dir.x * m_speed)]
		[(int)(s->player.pos.y)] == '0')
			s->player.pos.x -= s->player.dir.x * m_speed;
		if (s->map_a[(int)(s->player.pos.x)]
		[(int)(s->player.pos.y - s->player.dir.y * m_speed)] == '0')
			s->player.pos.y -= s->player.dir.y * m_speed;
	}
}

void	translate(t_scene *s, char f)
{
	double t_speed;

	t_speed = 0.5;
	if (f == 'l')
	{
		if (s->map_a[(int)(s->player.pos.x + -s->player.dir.y * t_speed)]
		[(int)(s->player.pos.y)] == '0')
			s->player.pos.x += -s->player.dir.y * t_speed;
		if (s->map_a[(int)(s->player.pos.x)]
		[(int)(s->player.pos.x + s->player.dir.x * t_speed)] == '0')
			s->player.pos.y += s->player.dir.x * t_speed;
	}
	else if (f == 'r')
	{
		if (s->map_a[(int)(s->player.pos.x + s->player.dir.y * t_speed)]
		[(int)(s->player.pos.y)] == '0')
			s->player.pos.x += s->player.dir.y * t_speed;
		if (s->map_a[(int)(s->player.pos.x)]
		[(int)(s->player.pos.x + -s->player.dir.x * t_speed)] == '0')
			s->player.pos.y += -s->player.dir.x * t_speed;
	}
}
