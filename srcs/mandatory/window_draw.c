/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 15:58:16 by mvaldes           #+#    #+#             */
/*   Updated: 2020/07/29 15:26:09 by mvaldes          ###   ########.fr       */
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

int		create_trgb_shade(int t, t_rgb color, int d)
{
	(void)d;
	if (d <= 1)
		return (t << 24 | color.r << 16 | color.g << 8 | color.b);
	return (t << 24 | (color.r / d << 16) | (color.g / d << 8)| color.b / d);
}

void	rgb_to_shade(t_screen_l *s_line, t_raycast *ray, t_scene *s)
{
	t_rgb	wall_N_clr = {255, 0, 0};
	t_rgb	wall_S_clr = {0, 255, 0};
	t_rgb	wall_E_clr = {255, 255, 0};
	t_rgb	wall_W_clr = {0, 0, 255};
	t_rgb	wall_clr = {0,0,0};

	if (ray->map.y > s->player.pos.y && ray->side == 1)//EST YELLOW
	{
		wall_clr.r = wall_E_clr.r;
		wall_clr.g = wall_E_clr.g;
		wall_clr.b = wall_E_clr.b;
	}
	else if (ray->map.y < s->player.pos.y && ray->side == 1)//WEST BLUE
	{
		wall_clr.r = wall_W_clr.r;
		wall_clr.g = wall_W_clr.g;
		wall_clr.b = wall_W_clr.b;
	}
	else if (ray->map.x < s->player.pos.x && ray->side == 0)//NORTH RED
	{
		wall_clr.r = wall_N_clr.r;
		wall_clr.g = wall_N_clr.g;
		wall_clr.b = wall_N_clr.b;
	}
	else if (ray->map.x > s->player.pos.x && ray->side == 0)//SOUTH GREEN
	{
		wall_clr.r = wall_S_clr.r;
		wall_clr.g = wall_S_clr.g;
		wall_clr.b = wall_S_clr.b;
	}
	s_line->c_wall = create_trgb_shade(0, wall_clr, ray->wall_d / 3);
	s_line->c_floor = create_trgb_shade(0, s->flr_clr, 0);
	s_line->c_ceil = create_trgb_shade(0, s->cei_clr, 0);
}

void			draw_pixel(t_env *env, int s_x, int pos_y, int color)
{
	*(int*)(env->mlx_img.data +
	(env->mlx_img.line_len * pos_y) +
	(s_x  * (env->mlx_img.bpp / 8))) = color;
}

static void			find_text_pix_color(t_scene *s, t_raycast *ray, t_texture *tex, t_screen_l *s_line)
{
	//calculate value of wallX
	// double wallX; //where exactly the wall was hit
	if (ray->side == 0)
		s_line->wallX = s->player.pos.y + ray->wall_d * ray->ray_dir.y;
	else
		s_line->wallX = s->player.pos.x + ray->wall_d * ray->ray_dir.x;
	s_line->wallX -= floor((s_line->wallX));

	//x coordinate on the texture
	s_line->texX = (int)(s_line->wallX * (double)(tex->width));
	if(ray->side == 0 && ray->ray_dir.x > 0)
		s_line->texX = tex->width - s_line->texX - 1;
	if(ray->side == 1 && ray->ray_dir.y < 0)
		s_line->texX = tex->width - s_line->texX - 1;
}

// int			find_pix_color(t_scene *s, t_raycast *ray, t_texture *tex, t_screen_l *s_line, int h)
// {
// 	(void)s;
// 	double step = 1.0 * tex->height / s_line->wall.height;
// 	// Starting texture coordinate
// 	double texPos = (s_line->wall.start - h / 2 + s_line->wall.height / 2) * step;
// 	for(int y = s_line->wall.start; y < s_line->wall.end; c)
// 	{
// 		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
// 		int texY = (int)texPos & (tex->height  - 1);
// 		texPos += step;
// 		uint32_t color = tex->img.data[tex->height  * texY + s_line->texX];
// 		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
// 		if (ray->side == 1)
// 			color = (color >> 1) & 8355711;
// 		// buffer[y][x] = color;
// 		return (color);
// 	}
// 	return (0);
// }

void			draw_vert_line(t_scene *s, t_env *env, t_raycast *ray, int s_x)
{
	int			h;
	int			pos_y;
	t_screen_l	s_line;

	h = s->screen.y;
	ft_bzero(&s_line, sizeof(s_line));
	calc_wall_height(&s_line, ray, h);
	find_text_pix_color(s, ray, &s->n_tex, &s_line);
	rgb_to_shade(&s_line, ray, s);

	double step = 1.0 * s->n_tex.height / s_line.wall.height;
	// Starting texture coordinate
	double texPos = (s_line.wall.start - h / 2 + s_line.wall.height / 2) * step;

	pos_y = 0;
	while (pos_y < s->screen.y)
	{
		if (pos_y >= s_line.wall.start && pos_y < s_line.wall.end)
		{
			int texY = (int)texPos;// & (s->n_tex.height  - 1)
			texPos += step;
			// int color = s->n_tex.img.data[s->n_tex.height  * texY + s_line.texX];
			// // if (ray->side == 1)
			// // 	color = (color >> 1) & 8355711;
			// printf("c : %d ", color);
			draw_pixel(env, s_x, pos_y, s->n_tex.img.data[s->n_tex.height  * texY + s_line.texX]);
		}
		else if (pos_y >= s_line.wall.end)
			draw_pixel(env, s_x, pos_y, s_line.c_floor);
		else
			draw_pixel(env, s_x, pos_y, s_line.c_ceil);
		pos_y++;
	}
}
