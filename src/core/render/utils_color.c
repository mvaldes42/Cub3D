/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 15:26:15 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/11 16:28:09 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int		create_trgb_shade(int t, t_rgb color, int d)
{
	if (d <= 1)
		return (t << 24 | color.r << 16 | color.g << 8 | color.b);
	return (t << 24 | (color.r / d << 16) | (color.g / d << 8) | color.b / d);
}

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

// static void		rgb_to_dec(t_screen_l *c_line, t_raycast *ray, t_scene *s)
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
// 	c_line->wl_hex = rgb_to_hex(wall_rgb.r, wall_rgb.g, wall_rgb.b);
// 	c_line->cei_hex = rgb_to_hex(s->cei_clr.r, s->cei_clr.g, s->cei_clr.b);
// 	c_line->fl_hex = rgb_to_hex(s->flr_clr.r, s->flr_clr.g, s->flr_clr.b);
// 	c_line->wl_dec = ft_atoi(ft_cvt_base(c_line->wl_hex, HEX_BASE, DEC_BASE));
// 	c_line->cei_dec = ft_atoi(ft_cvt_base(c_line->cei_hex, HEX_BASE, DEC_BASE));
// 	c_line->fl_dec = ft_atoi(ft_cvt_base(c_line->fl_hex, HEX_BASE, DEC_BASE));
// }
