/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 13:43:09 by mvaldes           #+#    #+#             */
/*   Updated: 2020/07/29 13:58:30 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		exit_game(t_env *env, int code)
{
	mlx_destroy_window(env->mlx_ptr, env->mlx_win);
	mlx_destroy_image(env->mlx_ptr, env->mlx_img.addr);
	if (env->scene.n_tex.img.addr)
		mlx_destroy_image(env->mlx_ptr, env->scene.n_tex.img.addr);
	if (env->scene.s_tex.img.addr)
		mlx_destroy_image(env->mlx_ptr, env->scene.s_tex.img.addr);
	if (env->scene.e_tex.img.addr)
		mlx_destroy_image(env->mlx_ptr, env->scene.e_tex.img.addr);
	if (env->scene.w_tex.img.addr)
		mlx_destroy_image(env->mlx_ptr, env->scene.w_tex.img.addr);
	if (env->scene.sprt_tex.img.addr)
		mlx_destroy_image(env->mlx_ptr, env->scene.sprt_tex.img.addr);
	if (env->scene.map_a)
		free(env->scene.map_a);
	exit(code);
	return (code);
}

int		exit_hook(t_env *env)
{
	return (exit_game(env, EXIT_SUCCESS));
}

int		key_press(int keycode, t_env *env)
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
