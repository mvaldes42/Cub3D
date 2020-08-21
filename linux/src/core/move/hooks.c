/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 15:37:12 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/19 21:53:18 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "move.h"

void		exit_sequence(t_env *env)
{
	int i;

	i = -1;
	if (env->mlx_img.addr)
		mlx_destroy_image(env->mlx_ptr, env->mlx_img.addr);
	while (++i < 5)
	{
		if (env->scene.tex[i].img.addr)
			mlx_destroy_image(env->mlx_ptr, env->scene.tex[i].img.addr);
		free_p(env->scene.tex[i].path);
	}
	if (env->mlx_win)
		mlx_destroy_window(env->mlx_ptr, env->mlx_win);
	i = 0;
	while (env->scene.map_a && i < env->scene.map_s && env->scene.map_a[i])
	{
		free(env->scene.map_a[i]);
		i++;
	}
	free_p(env->scene.map_a);
	free_p(env->scene.cam.z_buffer);
	free_p(env->scene.sprt.pos);
	close_fd(env->fd_prms);
	close_fd(env->fd_map_a);
	close_fd(env->fd_map_s);
}

static int		exit_game(t_env *env, int code)
{
	exit_sequence(env);
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
	else if (keycode == KEY_RIGHT)
		rotate(&(env->scene), -1);
	else if (keycode == KEY_Z)
		move(&(env->scene), 'f');
	else if (keycode == KEY_S)
		move(&(env->scene), 'b');
	else if (keycode == KEY_Q)
		translate(&(env->scene), 'l');
	else if (keycode == KEY_D)
		translate(&(env->scene), 'r');
	else if (keycode == KEY_ESC)
		exit_hook(env);
	draw_env(&(env->scene), env);
	return (1);
}

int				key_rel(int keycode, t_env *env)
{
	(void)keycode;
	mlx_clear_window(env->mlx_ptr, env->mlx_win);
	draw_env(&(env->scene), env);
	return (1);
}
