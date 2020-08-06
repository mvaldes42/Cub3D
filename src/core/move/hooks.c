/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 15:37:12 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/06 21:37:47 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int		exit_game(t_env *env, int code)
{
	int i;

	i = 0;
	mlx_destroy_window(env->mlx_ptr, env->mlx_win);
	mlx_destroy_image(env->mlx_ptr, env->mlx_img.addr);
	while (i < 5)
	{
		if (env->scene.env_text[i].img.addr)
			mlx_destroy_image(env->mlx_ptr, env->scene.env_text[i].img.addr);
		i++;
	}
	if (env->scene.map_a)
		free(env->scene.map_a);
	exit(code);
	return (code);
}

int				exit_hook(t_env *env)
{
	return (exit_game(env, EXIT_SUCCESS));
}

int				key_press(int keycode, t_env *env)
{
	mlx_clear_window(env->mlx_ptr, env->mlx_win);
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
