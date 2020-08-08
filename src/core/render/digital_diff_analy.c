/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digital_diff_analy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 16:07:48 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/07 18:47:12 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void find_step(t_raycast *ray_p, t_scene *scene_p)
{
	if (ray_p->ray_dir.x < 0)
	{
		ray_p->step.x = -1;
		ray_p->side_d.x = (scene_p->player.pos.x - (int)ray_p->map.x) *
						  ray_p->delta_d.x;
	}
	else
	{
		ray_p->step.x = 1;
		ray_p->side_d.x = ((int)ray_p->map.x + 1 - scene_p->player.pos.x) *
						  ray_p->delta_d.x;
	}
	if (ray_p->ray_dir.y < 0)
	{
		ray_p->step.y = -1;
		ray_p->side_d.y = (scene_p->player.pos.y - (int)ray_p->map.y) *
						  ray_p->delta_d.y;
	}
	else
	{
		ray_p->step.y = 1;
		ray_p->side_d.y = ((int)ray_p->map.y + 1 - scene_p->player.pos.y) *
						  ray_p->delta_d.y;
	}
}

static void find_wall(t_raycast *ray_p, t_scene *scene_p)
{
	while (ray_p->wall == 0)
	{
		if (ray_p->side_d.x < ray_p->side_d.y)
		{
			ray_p->side_d.x += ray_p->delta_d.x;
			ray_p->map.x += (int)ray_p->step.x;
			ray_p->side = 0;
		}
		else
		{
			ray_p->side_d.y += ray_p->delta_d.y;
			ray_p->map.y += (int)ray_p->step.y;
			ray_p->side = 1;
		}
		if (scene_p->map_a[(int)ray_p->map.x][(int)ray_p->map.y] == '1')
			ray_p->wall = 1;
	}
}

static void calc_dist_to_wall(t_raycast *ray_p, t_scene *scene)
{
	if (ray_p->side == 0)
		ray_p->wall_d = ((int)ray_p->map.x - scene->player.pos.x +
						 (1 - ray_p->step.x) / 2) /
						ray_p->ray_dir.x;
	else
		ray_p->wall_d = ((int)ray_p->map.y - scene->player.pos.y +
						 (1 - ray_p->step.y) / 2) /
						ray_p->ray_dir.y;
}

static void dig_diff_analy(t_raycast *ray_p, t_scene *s_p)
{
	ray_p->map.x = (int)s_p->player.pos.x;
	ray_p->map.y = (int)s_p->player.pos.y;
	if (ray_p->ray_dir.y == 0)
		ray_p->delta_d.x = 0;
	else
		ray_p->delta_d.x = (ray_p->ray_dir.x == 0) ? 1 : fabs(1 / ray_p->ray_dir.x);
	if (ray_p->ray_dir.x == 0)
		ray_p->delta_d.y = 0;
	else
		ray_p->delta_d.y = (ray_p->ray_dir.y == 0) ? 1 : fabs(1 / ray_p->ray_dir.y);
	find_step(ray_p, s_p);
	find_wall(ray_p, s_p);
	calc_dist_to_wall(ray_p, s_p);
}

static void sort_sprites_desc(t_scene *s, double *dist, int amount)
{
	int i;
	int j;
	int tmp;
	t_point tmp_pos;

	i = 0;
	while (i < amount)
	{
		j = i + 1;
		while (j < s->sprites.nbr_sprites)
		{
			if (dist[i] < dist[j])
			{
				tmp = dist[i];
				tmp_pos = s->sprites.position[i];
				s->sprites.position[i] = s->sprites.position[j];
				dist[i] = dist[j];
				s->sprites.position[j] = tmp_pos;
				dist[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void draw_pixel(t_env *env, int s_x, int pos_y, int color)
{
	*(int *)(env->mlx_img.data +
			 (env->mlx_img.line_len * pos_y) +
			 (s_x * (env->mlx_img.bpp / 8))) = color;
}

static void draw_sprites(t_scene *s, t_env *env, t_raycast *ray_p)
{
	int i;
	int num_sprite;
	int sprite_order[s->sprites.nbr_sprites];
	double sprite_dist[s->sprites.nbr_sprites];
	(void)ray_p;

	// t_data sprite_img;
	// ft_bzero(&sprite_img, sizeof(sprite_img));
	// if (!(sprite_img.addr = mlx_new_image(env->mlx_ptr, env->scene.screen.x, env->scene.screen.y)) ||
	// 	!(sprite_img.data = mlx_get_data_addr(sprite_img.addr, &env->mlx_img.bpp, &env->mlx_img.line_len, &env->mlx_img.endian)))
	// 	exit_message_failure();
	num_sprite = s->sprites.nbr_sprites;
	i = 0;
	while (i < s->sprites.nbr_sprites)
	{
		sprite_order[i] = i;
		sprite_dist[i] = ((s->player.pos.x - s->sprites.position[i].x) * (s->player.pos.x - s->sprites.position[i].x) + (s->player.pos.y - s->sprites.position[i].y) * (s->player.pos.y - s->sprites.position[i].y));
		i++;
	}
	sort_sprites_desc(s, sprite_dist, num_sprite);
	// i = 0;
	// while (i < s->sprites.nbr_sprites)
	// {
	// 	printf("%f\n", s->sprites.position[i].x);
	// 	i++;
	// }
	for (int i = 0; i < num_sprite; i++)
	{
		//translate sprite position to relative to camera
		double spriteX = s->sprites.position[i].x - s->player.pos.x;
		double spriteY = s->sprites.position[i].y - s->player.pos.y;
		double inv_det = 1.0 / (s->cam.pln_dir.x * s->player.dir.y - s->player.dir.x * s->cam.pln_dir.y); //required for correct matrix multiplication
		double transform_x = inv_det * (s->player.dir.y * spriteX - s->player.dir.x * spriteY);
		double transform_y = inv_det * (-s->player.dir.y * spriteX + s->cam.pln_dir.x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D
		int sprites_screen_x = (int)((s->screen.x / 2) * (1 + transform_x / transform_y));
		//calculate height of the sprite on screen
		int sprite_h = abs((int)(s->screen.y / transform_y)); //using 'transform_y' instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int draw_start_y = (-sprite_h / 2 + s->screen.y / 2) < 0 ? 0 : -sprite_h / 2 + s->screen.y / 2;
		int draw_end_y = (sprite_h / 2 + s->screen.y / 2) >= s->screen.y ? s->screen.y - 1 : sprite_h / 2 + s->screen.y / 2;
		//calculate width of the sprite
		int sprite_w = abs((int)(s->screen.y / transform_y));
		int draw_start_x = (-sprite_w / 2 + sprites_screen_x) < 0 ? 0 : -sprite_w / 2 + sprites_screen_x;
		int draw_end_x = (sprite_w / 2 + sprites_screen_x) >= s->screen.x ? s->screen.x - 1 : sprite_w / 2 + sprites_screen_x;
		for (int stripe = draw_start_x; stripe < draw_end_x; stripe++)
		{
			//int texX = (int)(256 * (stripe - (-sprite_w / 2 + sprites_screen_x)) * 64 / sprite_w) / 256;
			int texX = (int)(256 * (stripe - (-sprite_w / 2 + sprites_screen_x)) * 64 / sprite_w) / 256;
			if (transform_y > 0 && stripe > 0 && stripe < s->screen.x && transform_y < env->scene.cam.z_buffer[stripe])
			{
				for (int y = draw_start_y + 1; y < draw_end_y; y++) //for every pixel of the current stripe
				{
					int d = y * 256 - s->screen.y * 128 + sprite_h * 128; //256 and 128 factors to avoid floats
					int texY = ((d * s->env_text[4].height) / sprite_h) / 256;
					// Uint32 color = s->env_text[sprite[spriteOrder[i]].texture][64 * texY + texX]; //get current color from the texture
					unsigned int tex_col = ((unsigned int *)s->env_text[4].img.data)[(int)(texY * s->env_text[4].width + texX)];
					if ((tex_col & 0x00FFFFFF) != 0)
						draw_pixel(env, stripe, y, tex_col); //paint pixel if it isn't black, black is the invisible color
															 // mlx_pixel_put(env->mlx_ptr, env->mlx_win, stripe, y, tex_col);
				}
			}
		}
	}
	mlx_put_image_to_window(env->mlx_ptr, env->mlx_win, env->mlx_img.addr, 0, 0);
}

void draw_env(t_scene *s_p, t_env *e)
{
	int i;
	double w;
	double cam_x;
	t_raycast raycast;
	t_raycast *ray_p;

	ray_p = &raycast;
	i = 0;
	w = s_p->screen.x;
	while (i < w)
	{
		ft_bzero(&raycast, sizeof(raycast));
		cam_x = ((2 * i) / (w - 1)) - 1;
		ray_p->ray_dir.x = s_p->player.dir.x + s_p->cam.pln_dir.x * cam_x;
		ray_p->ray_dir.y = s_p->player.dir.y + s_p->cam.pln_dir.y * cam_x;
		dig_diff_analy(&raycast, s_p);
		draw_vert_line(s_p, e, ray_p, i);
		s_p->cam.z_buffer[i] = ray_p->wall_d;
		i++;
	}
	mlx_put_image_to_window(e->mlx_ptr, e->mlx_win, e->mlx_img.addr, 0, 0);
	draw_sprites(s_p, e, ray_p);
}
/*
**	printf("scene_p->player.pos.x : %f\n", scene_p->player.pos.x);
**	printf("scene_p->player.pos.y : %f\n", scene_p->player.pos.y);
**	printf("scene_ptr->player.dir.x : %f\n", scene_p->player.dir.x);
**	printf("scene_ptr->player.dir.y : %f\n", scene_p->player.dir.y);
**	printf("scene_ptr->cam.pln_dir.x : %f\n", scene_p->cam.pln_dir.x);
**	printf("scene_ptr->cam.pln_dir.y : %f\n", scene_p->cam.pln_dir.y);
**	printf("scene_ptr->cam.pln_len : %f\n", scene_p->cam.pln_len);
**	printf("scene_ptr->cam.dir_len  : %f\n", scene_p->cam.dir_len);
*/
