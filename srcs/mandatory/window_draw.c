/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 15:58:16 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/05 15:28:24 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		calc_wall_height(t_scene *s, t_screen_l *line, t_raycast *ray)
{
	int h;

	h = s->screen.y;
	line->wall.height = (int)(h / ray->wall_d);
	line->wall.start = -line->wall.height / 2 + h / 2;
	if (line->wall.start < 0)
		line->wall.start = 0;
	line->wall.end = line->wall.height / 2 + h / 2;
	if (line->wall.end >= h)
		line->wall.end = h - 1;
}

static int		find_wall_orient(t_raycast *ray, t_scene *s)
{
	int		wall_orient;

	wall_orient = 0;
	if (ray->map.y > s->player.pos.y && ray->side == 1)
		wall_orient = 2;
	else if (ray->map.y < s->player.pos.y && ray->side == 1)
		wall_orient = 3;
	else if (ray->map.x > s->player.pos.x && ray->side == 0)
		wall_orient = 1;
	return (wall_orient);
}

static void		draw_pixel(t_env *env, int s_x, int pos_y, int color)
{
	*(int*)(env->mlx_img.data +
	(env->mlx_img.line_len * pos_y) +
	(s_x * (env->mlx_img.bpp / 8))) = color;
}

static void		calc_pix_variables(t_scene *s, t_raycast *ray,
				t_screen_l *c_line)
{
	t_texture *tex;

	calc_wall_height(s, c_line, ray);
	c_line->orient = find_wall_orient(ray, s);
	tex = &(s->env_text[c_line->orient]);
	if (ray->side == 0)
		c_line->wall_x = s->player.pos.y + ray->wall_d * ray->ray_dir.y;
	else
		c_line->wall_x = s->player.pos.x + ray->wall_d * ray->ray_dir.x;
	c_line->wall_x -= floor((c_line->wall_x));
	c_line->text_x = (int)(c_line->wall_x * (double)(tex->width));
	if (ray->side == 0 && ray->ray_dir.x > 0)
		c_line->text_x = tex->width - c_line->text_x - 1;
	if (ray->side == 1 && ray->ray_dir.y < 0)
		c_line->text_x = tex->width - c_line->text_x - 1;
	c_line->step = 1.0 * tex->height / c_line->wall.height;
	c_line->texel_pos = (c_line->wall.start - s->screen.y / 2 +
	c_line->wall.height / 2) * c_line->step;
	c_line->c_floor = create_trgb_shade(0, s->env_col[1], 0);
	c_line->c_ceil = create_trgb_shade(0, s->env_col[0], 0);
}

void			draw_vert_line(t_scene *s, t_env *env, t_raycast *ray, int s_x)
{
	int				pos_y;
	t_screen_l		c_line;
	unsigned int	tex_col;

	ft_bzero(&c_line, sizeof(c_line));
	calc_pix_variables(s, ray, &c_line);
	pos_y = 0;
	while (pos_y < s->screen.y)
	{
		if (pos_y >= c_line.wall.start && pos_y < c_line.wall.end)
		{
			c_line.texel_pos += c_line.step;
			tex_col = ((unsigned int*)s->env_text[c_line.orient].img.data)
			[(int)(s->env_text[c_line.orient].width *
			(int)c_line.texel_pos + c_line.text_x)];
			if (ray->side == 1)
				tex_col = (tex_col >> 1) & 8355711;
			draw_pixel(env, s_x, pos_y, tex_col);
		}
		else if (pos_y >= c_line.wall.end)
			draw_pixel(env, s_x, pos_y, c_line.c_floor);
		else
			draw_pixel(env, s_x, pos_y, c_line.c_ceil);
		pos_y++;
	}
}
