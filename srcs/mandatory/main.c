/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:11:43 by mvaldes           #+#    #+#             */
/*   Updated: 2020/07/28 16:31:53 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char		*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
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
	env.mlx_img.data = mlx_get_data_addr(env.mlx_img.addr , &env.mlx_img.bits_per_pixel, &env.mlx_img.line_length, &env.mlx_img.endian);
/*
**	img.img = mlx_new_image(env.mlx_ptr, 1920, 1080);
**	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
**	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
**	mlx_put_image_to_window(env.mlx_ptr, env.mlx_win, img.img, 0, 0);
*/
	mlx_hook(env.mlx_win, X_EVENT_KEY_PRESS, 0, &key_press, &env);
	mlx_hook(env.mlx_win, X_EVENT_EXIT, 0, &exit_hook, &env);
	draw_env(&(env.scene), &env);
	mlx_loop(env.mlx_ptr);
	return (0);
}
