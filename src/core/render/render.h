/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 10:28:23 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/07 10:43:29 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RENDER_H
# define __RENDER_H
# include "../cub3d.h"
# include <math.h>

typedef struct	s_line
{
	int	start;
	int	end;
	int	height;
}				t_line;

typedef struct	s_screen_l
{
	t_line	wall;
	int		c_wall;
	int		c_floor;
	int		c_ceil;
	double	wall_x;
	int		text_x;
	int		text_y;
	double	step;
	double	texel_pos;
	int		orient;

}				t_screen_l;

typedef struct	s_raycast
{
	t_point	ray_dir;
	t_point	map;
	t_point	side_d;
	t_point	delta_d;
	t_point	step;
	int		wall;
	int		side;
	double	wall_d;
}				t_raycast;

void			draw_vert_line(t_scene *scene_p, t_env *env_p,
				t_raycast *raycast_p, int i);
void			window_resize(t_scene *scene_p);
int				create_trgb_shade(int t, t_rgb color, int d);

#endif
