/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digitalDifAnaly.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 16:07:48 by mvaldes           #+#    #+#             */
/*   Updated: 2020/07/22 15:27:27 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	find_step(t_raycast *raycast_p, t_scene *scene_p)
{
	if (raycast_p->ray_dir.x < 0)
	{
	raycast_p->step.x = -1;
	raycast_p->side_dist.x = (scene_p->player.pos.x - (int)raycast_p->map.x) *
	raycast_p->delta_dist.x;
	}
	else
	{
	raycast_p->step.x = 1;
	raycast_p->side_dist.x = ((int)raycast_p->map.x + 1 - scene_p->player.pos.x) *
	raycast_p->delta_dist.x;
	}
	if (raycast_p->ray_dir.y < 0)
	{
	raycast_p->step.y = -1;
	raycast_p->side_dist.y = (scene_p->player.pos.y - (int)raycast_p->map.y) *
	raycast_p->delta_dist.y;
	}
	else
	{
	raycast_p->step.y = 1;
	raycast_p->side_dist.y = ((int)raycast_p->map.y + 1 - scene_p->player.pos.y) *
	raycast_p->delta_dist.y;
	}
}

static void find_wall(t_raycast *raycast_p, t_scene *scene_p)
{
	while (raycast_p->wall == 0)
	{
		// printf("side_dist.x : %f / side_dist.y : %f / ", raycast_p->side_dist.x, raycast_p->side_dist.y);
		// printf("delta_dist.x : %f / delta_dist.y : %f / ",raycast_p->delta_dist.x, raycast_p->delta_dist.y);
		if (raycast_p->side_dist.x < raycast_p->side_dist.y)
		{
			raycast_p->side_dist.x += raycast_p->delta_dist.x;
			raycast_p->map.x += (int)raycast_p->step.x;
			raycast_p->side = 0;
		}
		else
		{
			raycast_p->side_dist.y += raycast_p->delta_dist.y;
			raycast_p->map.y += (int)raycast_p->step.y;
			raycast_p->side = 1;
		}
		if (scene_p->map_a[(int)raycast_p->map.x][(int)raycast_p->map.y] == '1')
		{
			raycast_p->wall = 1;
			// printf("wall x : %d, wall y: %d\n\n", ((int)raycast_p->map.x), ((int)raycast_p->map.y));
		}
	}
}

static void calc_dist_to_wall(t_raycast *raycast_p, t_scene *scene)
{
	if (raycast_p->side == 0)
		raycast_p->wall_dist = ((int)raycast_p->map.x - scene->player.pos.x +
		(1 - raycast_p->step.x) / 2) / raycast_p->ray_dir.x;
	else
		raycast_p->wall_dist = ((int)raycast_p->map.y - scene->player.pos.y +
		(1 - raycast_p->step.y) / 2) / raycast_p->ray_dir.y;
}

static void dig_diff_analy(t_raycast *raycast_p, t_scene *scene_p)
{
	raycast_p->map.x = (int)scene_p->player.pos.x;
	raycast_p->map.y = (int)scene_p->player.pos.y;
	raycast_p->delta_dist.x = (raycast_p->ray_dir.y == 0) ? 0 : ((raycast_p->ray_dir.x == 0) ? 1 : fabs(1 / raycast_p->ray_dir.x));
	raycast_p->delta_dist.y = (raycast_p->ray_dir.x == 0) ? 0 : ((raycast_p->ray_dir.y == 0) ? 1 : fabs(1 / raycast_p->ray_dir.y));
	find_step(raycast_p, scene_p);
	find_wall(raycast_p, scene_p);
	calc_dist_to_wall(raycast_p, scene_p);
}

int		display(int nb, char *str, char *result, int index)
{
	unsigned int	nbr;
	unsigned int	str_length;

	str_length = 0;
	while (str[str_length])
		str_length++;
	if (nb < 0)
	{
		result[index++] = '-';
		nbr = nb * -1;
	}
	else
		nbr = nb;
	if (nbr >= str_length)
		display(nbr / str_length, str, result, index - 1);
	result[index] = str[nbr % str_length];
	return (index);
}

int		get_number_length(int number, char *base)
{
	int	length;
	int	base_length;

	base_length = 0;
	while (base[base_length])
		base_length++;
	length = 0;
	while (number >= base_length)
	{
		++length;
		number /= base_length;
	}
	return (++length);
}

int		get_nb(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i] && base[i] != c)
		i++;
	return (i);
}

int		ft_atoi_base(char *str, char *base)
{
	int	s;
	int	i;
	int	res;
	int	negative;
	int	base_length;

	base_length = 0;
	while (base[base_length])
		++base_length;
	s = 0;
	while (str[s] != '\0' && (str[s] == ' ' || str[s] == '\t' || str[s] == '\r'
				|| str[s] == '\n' || str[s] == '\v' || str[s] == '\f'))
		s++;
	i = s - 1;
	res = 0;
	negative = 1;
	while (str[++i] && (((str[i] == '-' || str[i] == '+') && i == s) ||
				(str[i] != '-' && str[i] != '+')))
		if (str[i] == '-')
			negative = -1;
		else if (str[i] != '+')
			res = (res * base_length) + (get_nb(str[i], base));
	return (res * negative);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	char			*result;
	int				number;
	int				last_index;

	if (!nbr || !base_from || !base_to)
		return (0);
	number = ft_atoi_base(nbr, base_from);
	result = malloc(sizeof(char) * get_number_length(number, base_to));
	last_index = display(number, base_to, result,
		get_number_length(number, base_to) - 1);
	result[last_index + 1] = '\0';
	return (result);
}

static char *from_rgb_to_hex(int r, int g, int b)
{
	char *base16 = "0123456789ABCDEF";
	char *base10 = "0123456789";
	char *hex_color;
	char *src;

	if (!(hex_color = (char *)malloc(sizeof(char) * (7 + 1))))
		return (NULL);
	if (!(src = (char *)malloc(sizeof(char) * (2 + 1))))
		return (NULL);
	if ((r >= 0 && r<= 255) && (g >= 0 && g <= 255) && (b >= 0 && b <= 255))
	{
		// hex_color[0] = '#';
		if (r == 0)
		{
			strcat(hex_color, ft_convert_base(ft_itoa(r), base10, base16));
		}
		strcat(hex_color, ft_convert_base(ft_itoa(r), base10, base16));
		if (g == 0)
		{
			strcat(hex_color, ft_convert_base(ft_itoa(g), base10, base16));
		}
		strcat(hex_color, ft_convert_base(ft_itoa(g), base10, base16));
		if (b == 0)
		{
			strcat(hex_color, ft_convert_base(ft_itoa(b), base10, base16));
		}
		strcat(hex_color, ft_convert_base(ft_itoa(b), base10, base16));
	}
	return (hex_color);
}

static void	draw_walls(t_scene *scene_p, t_env *env_p, t_raycast *raycast_p, int i)
{
	//Calculate height of line to draw on screen
	int lineHeight;
	int h = scene_p->screen.y;
	int j;
	char *wall_hex;
	char *cei_hex;
	char *floor_hex;

	lineHeight = (int)(h / raycast_p->wall_dist);

	//calculate lowest and highest pixel to fill in current stripe
	int drawStart = -lineHeight / 2 + h / 2;
	if(drawStart < 0)drawStart = 0;
	int drawEnd = lineHeight / 2 + h / 2;
	if(drawEnd >= h)drawEnd = h - 1;

	// choose wall color
	t_rgb wall_rgb = {38, 70, 83};
	if (raycast_p->side == 0)
	{
		wall_rgb.r = wall_rgb.r / 1.5;
		wall_rgb.g = wall_rgb.g / 1.5;
		wall_rgb.b = wall_rgb.b / 1.5;
	}
	wall_hex = from_rgb_to_hex(wall_rgb.r, wall_rgb.g, wall_rgb.b);
	cei_hex = from_rgb_to_hex(scene_p->cei_clr.r, scene_p->cei_clr.g, scene_p->cei_clr.b);
	floor_hex = from_rgb_to_hex(scene_p->flr_clr.r, scene_p->flr_clr.g, scene_p->flr_clr.b);
	j = 0;
	while (j < scene_p->screen.y)
	{
		while (j >= drawStart && j < drawEnd)
		{
			mlx_pixel_put(env_p->mlx_ptr, env_p->mlx_win, i, j, ft_atoi(ft_convert_base(wall_hex, "0123456789ABCDEF" ,"0123456789")));
			j++;
		}
		if (j >= drawEnd)
			mlx_pixel_put(env_p->mlx_ptr, env_p->mlx_win, i, j, ft_atoi(ft_convert_base(floor_hex, "0123456789ABCDEF" ,"0123456789")));
		else
			mlx_pixel_put(env_p->mlx_ptr, env_p->mlx_win, i, j, ft_atoi(ft_convert_base(cei_hex, "0123456789ABCDEF" ,"0123456789")));
		j++;
	}
}

void	cast_rays_to_wall(t_scene *scene_p, t_env *env_p)
{
	int i;
	double w;
	double camera_x;
	t_raycast raycast;
	t_raycast *raycast_p;

	raycast_p = &raycast;
	i = 0;
	w = scene_p->screen.x;
	while(i < w)
	{
		ft_bzero(&raycast, sizeof(raycast));
		camera_x = ((2 * i) / (w - 1)) - 1;
		raycast_p->ray_dir.x = scene_p->player.dir.x + scene_p->camera.planeDir.x * camera_x;
		raycast_p->ray_dir.y = scene_p->player.dir.y + scene_p->camera.planeDir.y * camera_x;
		dig_diff_analy(&raycast, scene_p);
		draw_walls(scene_p, env_p, raycast_p, i);
		// printf("i : %d & ray_dir.x : %f & ray_dir.y : %f & camera_x: %f & dist_wall : %f\n", i, raycast_p->ray_dir.x, raycast_p->ray_dir.y, camera_x, raycast_p->wall_dist);
		i++;
	}
	// printf("scene_p->player.pos.x : %f\n", scene_p->player.pos.x);
	// printf("scene_p->player.pos.y : %f\n", scene_p->player.pos.y);
	// printf("scene_ptr->player.dir.x : %f\n", scene_p->player.dir.x);
	// printf("scene_ptr->player.dir.y : %f\n", scene_p->player.dir.y);
	// printf("scene_ptr->camera.planeDir.x : %f\n", scene_p->camera.planeDir.x);
	// printf("scene_ptr->camera.planeDir.y : %f\n", scene_p->camera.planeDir.y);
	// printf("scene_ptr->camera.planeLength : %f\n", scene_p->camera.planeLength);
	// printf("scene_ptr->camera.dirLength  : %f\n", scene_p->camera.dirLength);
}



