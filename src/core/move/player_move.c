/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 16:22:32 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/10 14:39:11 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "move.h"

void	rotate(t_scene *s, int f)
{
	double r_speed;
	double old_dir_x;
	double old_plane_x;

	r_speed = 0.10;
	old_dir_x = s->plyr.dir.x;
	s->plyr.dir.x = s->plyr.dir.x * cos(f * r_speed)
	- s->plyr.dir.y * sin(f * r_speed);
	s->plyr.dir.y = old_dir_x * sin(f * r_speed)
	+ s->plyr.dir.y * cos(f * r_speed);
	old_plane_x = s->cam.pln.x;
	s->cam.pln.x = s->cam.pln.x * cos(f * r_speed)
	- s->cam.pln.y * sin(f * r_speed);
	s->cam.pln.y = old_plane_x * sin(f * r_speed)
	+ s->cam.pln.y * cos(f * r_speed);
}

void	move(t_scene *s, char f)
{
	double m_speed;

	m_speed = 0.3;
	if (f == 'f')
	{
		if (s->map_a[(int)(s->plyr.pos.x + s->plyr.dir.x * m_speed)]
		[(int)(s->plyr.pos.y)] == '0')
			s->plyr.pos.x += s->plyr.dir.x * m_speed;
		if (s->map_a[(int)(s->plyr.pos.x)]
		[(int)(s->plyr.pos.y + s->plyr.dir.y * m_speed)] == '0')
			s->plyr.pos.y += s->plyr.dir.y * m_speed;
	}
	else if (f == 'b')
	{
		if (s->map_a[(int)(s->plyr.pos.x - s->plyr.dir.x * m_speed)]
		[(int)(s->plyr.pos.y)] == '0')
			s->plyr.pos.x -= s->plyr.dir.x * m_speed;
		if (s->map_a[(int)(s->plyr.pos.x)]
		[(int)(s->plyr.pos.y - s->plyr.dir.y * m_speed)] == '0')
			s->plyr.pos.y -= s->plyr.dir.y * m_speed;
	}
}

void	translate(t_scene *s, char f)
{
	double t_speed;

	t_speed = 0.3;
	if (f == 'l')
	{
		if (s->map_a[(int)(s->plyr.pos.x + -s->plyr.dir.y * t_speed)]
		[(int)(s->plyr.pos.y)] == '0')
			s->plyr.pos.x += -s->plyr.dir.y * t_speed;
		if (s->map_a[(int)(s->plyr.pos.x)]
		[(int)(s->plyr.pos.x + s->plyr.dir.x * t_speed)] == '0')
			s->plyr.pos.y += s->plyr.dir.x * t_speed;
	}
	else if (f == 'r')
	{
		if (s->map_a[(int)(s->plyr.pos.x + s->plyr.dir.y * t_speed)]
		[(int)(s->plyr.pos.y)] == '0')
			s->plyr.pos.x += s->plyr.dir.y * t_speed;
		if (s->map_a[(int)(s->plyr.pos.x)]
		[(int)(s->plyr.pos.x + -s->plyr.dir.x * t_speed)] == '0')
			s->plyr.pos.y += -s->plyr.dir.x * t_speed;
	}
}
