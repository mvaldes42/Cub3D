/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:11:43 by mvaldes           #+#    #+#             */
/*   Updated: 2020/07/29 11:30:19 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char		*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int		exit_game(t_env *env, int code)
{
	mlx_destroy_window(env->mlx_ptr, env->mlx_win);
	exit(code);
	return (code);
}

int		exit_hook(t_env *env)
{
	return (exit_game(env, EXIT_SUCCESS));
}

int		key_press(int keycode, t_env *env)
{
	// mlx_clear_window(env->mlx_ptr, env->mlx_win);
	if (keycode == KEY_LEFT)
		rotate(&(env->scene), 1);
	if (keycode == KEY_RIGHT)
		rotate(&(env->scene), -1);
	if (keycode == KEY_W)
		move(&(env->scene), 'f');
	if (keycode == KEY_S)
		move(&(env->scene), 'b');
	if (keycode == KEY_A)
		translate(&(env->scene), 'l');
	if (keycode == KEY_D)
		translate(&(env->scene), 'r');
	else if (keycode == KEY_ESC)
		exit_hook(env);
	draw_env(&(env->scene), env);
	return (0);
}

static int		load_xpm_texture(t_env *env, t_texture *text)
{
	printf("text->path : %s\n", text->path);
	if (text->path)
	{
		if ((text->img.addr = mlx_xpm_file_to_image(env->mlx_ptr,
			text->path, &text->width, &text->height)))
			text->img.data = mlx_get_data_addr(text->img.addr,
				&text->img.bpp, &text->img.line_len, &text->img.endian);
		else
		{
			g_error = 4;
			return (0);
		}
	}
	return (1);
}

static void		load_game_textures(t_env *env_p, t_scene *scene_p)
{
	if (! load_xpm_texture(env_p, &(scene_p->n_tex)) ||
	!load_xpm_texture(env_p, &(scene_p->s_tex)) ||
	!load_xpm_texture(env_p, &(scene_p->e_tex)) ||
	!load_xpm_texture(env_p, &(scene_p->w_tex)) ||
	!load_xpm_texture(env_p, &(scene_p->sprt_tex)))
		exit_message_failure();
}

int		main(int argc, char *argv[])
{
	t_env		env;

	(void)argc;
	ft_bzero(&env, sizeof(env));
	init_scene(argv, &(env.scene));
	if ((env.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((env.mlx_win = mlx_new_window(env.mlx_ptr, env.scene.screen.x, env.scene.screen.y, "Loulou's Awesome Game")) == NULL)
		return (EXIT_FAILURE);
	env.mlx_img.addr = mlx_new_image(env.mlx_ptr, env.scene.screen.x, env.scene.screen.y);
	env.mlx_img.data = mlx_get_data_addr(env.mlx_img.addr , &env.mlx_img.bpp, &env.mlx_img.line_len, &env.mlx_img.endian);
	load_game_textures(&env, &(env.scene));
/*
**	img.img = mlx_new_image(env.mlx_ptr, 1920, 1080);
**	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
**	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
**	mlx_put_image_to_window(env.mlx_ptr, env.mlx_win, img.img, 0, 0);
*/
	mlx_hook(env.mlx_win, X_EVENT_KEY_PRESS, 0, &key_press, &env);
	mlx_hook(env.mlx_win, X_EVENT_EXIT, 0, &exit_hook, &env);
	draw_env(&(env.scene), &env);
	mlx_loop(env.mlx_ptr);
	return (0);
}
