/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 15:58:16 by mvaldes           #+#    #+#             */
/*   Updated: 2020/07/28 15:17:32 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static char		*rgb_to_hex(int r, int g, int b)
// {
// 	char *hex_color;
// 	char *src;

// 	if (!(hex_color = (char *)malloc(sizeof(char) * (7 + 1))))
// 		return (NULL);
// 	if (!(src = (char *)malloc(sizeof(char) * (2 + 1))))
// 		return (NULL);
// 	if ((r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0 && b <= 255))
// 	{
// 		if (r == 0)
// 			strcat(hex_color, ft_cvt_base(ft_itoa(r), DEC_BASE, HEX_BASE));
// 		strcat(hex_color, ft_cvt_base(ft_itoa(r), DEC_BASE, HEX_BASE));
// 		if (g == 0)
// 			strcat(hex_color, ft_cvt_base(ft_itoa(g), DEC_BASE, HEX_BASE));
// 		strcat(hex_color, ft_cvt_base(ft_itoa(g), DEC_BASE, HEX_BASE));
// 		if (b == 0)
// 			strcat(hex_color, ft_cvt_base(ft_itoa(b), DEC_BASE, HEX_BASE));
// 		strcat(hex_color, ft_cvt_base(ft_itoa(b), DEC_BASE, HEX_BASE));
// 	}
// 	return (hex_color);
// }

static void		calc_wall_height(t_screen_l *line, t_raycast *ray, int h)
{
	line->wall.height = (int)(h / ray->wall_d);
	line->wall.start = -line->wall.height / 2 + h / 2;
	if (line->wall.start < 0)
		line->wall.start = 0;
	line->wall.end = line->wall.height / 2 + h / 2;
	if (line->wall.end >= h)
		line->wall.end = h - 1;
}

// static void		rgb_to_dec(t_screen_l *s_line, t_raycast *ray, t_scene *s)
// {
// 	t_rgb		wall_rgb;

// 	wall_rgb.r = 38;
// 	wall_rgb.g = 70;
// 	wall_rgb.b = 83;
// 	if (ray->side == 0)
// 	{
// 		wall_rgb.r = wall_rgb.r / 1.5;
// 		wall_rgb.g = wall_rgb.g / 1.5;
// 		wall_rgb.b = wall_rgb.b / 1.5;
// 	}
// 	s_line->wl_hex = rgb_to_hex(wall_rgb.r, wall_rgb.g, wall_rgb.b);
// 	s_line->cei_hex = rgb_to_hex(s->cei_clr.r, s->cei_clr.g, s->cei_clr.b);
// 	s_line->fl_hex = rgb_to_hex(s->flr_clr.r, s->flr_clr.g, s->flr_clr.b);
// 	s_line->wl_dec = ft_atoi(ft_cvt_base(s_line->wl_hex, HEX_BASE, DEC_BASE));
// 	s_line->cei_dec = ft_atoi(ft_cvt_base(s_line->cei_hex, HEX_BASE, DEC_BASE));
// 	s_line->fl_dec = ft_atoi(ft_cvt_base(s_line->fl_hex, HEX_BASE, DEC_BASE));
// }


int		create_trgb_shade(int t, int r, int g, int b, int d)
{
	return (t << 24 | (r / d) << 16 | (g / d) << 8 | (b / d));
}

void			draw_vert_line(t_scene *s, t_env *env, t_raycast *ray, int s_x)
{
	int			h;
	int			pos_y;
	t_screen_l	s_line;
	// t_rgb		wall_rgb;

	h = s->screen.y;
	ft_bzero(&s_line, sizeof(s_line));
	calc_wall_height(&s_line, ray, h);
	// rgb_to_dec(&s_line, ray, s);
	int color = create_trgb_shade(0, 233, 196, 106, (int)(ray->wall_d));
	int colorfl = create_trgb_shade(0, 226, 149, 120, 1);
	int colorcei = create_trgb_shade(0, 168, 218, 220, 1);
	pos_y = 0;
	while (pos_y < s->screen.y)
	{
		while (pos_y >= s_line.wall.start && pos_y < s_line.wall.end)
		{
			*(int*)(env->mlx_img.data + (4 * (int)s->screen.x * (int)pos_y) + ((int)s_x  * 4)) = color;
			pos_y++;
		}
		if (pos_y >= s_line.wall.end)
			*(int*)(env->mlx_img.data + (4 * (int)s->screen.x * (int)pos_y) + ((int)s_x  * 4)) = colorfl;
		else
			*(int*)(env->mlx_img.data + (4 * (int)s->screen.x * (int)pos_y) + ((int)s_x  * 4)) = colorcei;

		pos_y++;
	}
}
