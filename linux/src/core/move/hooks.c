/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 15:37:12 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/12 23:31:20 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "move.h"

static void		free_p(void *p)
{
	if (p)
		free(p);
}

static int		exit_game(t_env *env, int code)
{
	int i;
	int mx_line;

	mx_line = get_max_line(env->scene.map);
	i = -1;
	if (env->mlx_img.addr)
		mlx_destroy_image(env->mlx_ptr, env->mlx_img.addr);
	while (++i < 5)
		if (env->scene.tex[i].img.addr)
			mlx_destroy_image(env->mlx_ptr, env->scene.tex[i].img.addr);
	if (env->mlx_win)
		mlx_destroy_window(env->mlx_ptr, env->mlx_win);
	i = 0;
	while (i < ft_lstsize_map(env->scene.map))
	{
		free(env->scene.map_a[i]);
		i++;
	}
	free_p(env->scene.map_a);
	free_p(env->scene.cam.z_buffer);
	free_p(env->scene.sprt.pos);
	free_p(env->scene.sprt.dst);
	close(env->fd);
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
	if (keycode == KEY_Z)
		move(&(env->scene), 'f');
	if (keycode == KEY_S)
		move(&(env->scene), 'b');
	if (keycode == KEY_Q)
		translate(&(env->scene), 'l');
	if (keycode == KEY_D)
		translate(&(env->scene), 'r');
	else if (keycode == KEY_ESC)
		exit_hook(env);
	draw_env(&(env->scene), env);
	return (0);
}
