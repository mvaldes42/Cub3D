/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:11:43 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/13 22:01:55 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "initialize/initialize.h"
#include "./snapshot/bmp.h"

static void	mlx_do_loop(t_env *env)
{
	mlx_hook(env->mlx_win, X_EVENT_KEY_PRESS, (1L << 0), &key_press, env);
	mlx_hook(env->mlx_win, X_EVENT_KEY_RELEASE, (1L << 0), &key_rel, env);
	mlx_hook(env->mlx_win, X_EVENT_EXIT, (1L << 17), &exit_hook, env);
	mlx_loop(env->mlx_ptr);
}

int			main(int argc, char *argv[])
{
	t_env		env;

	ft_bzero(&env, sizeof(env));
	if (argc > 2 && ft_strlen(argv[2]) == 6 &&
	ft_strncmp(argv[2], "--save", 6) == 0)
		env.save = 1;
	if ((argc == 3 && env.save == 0) || argc > 3)
		exit_message_failure(14);
	env.fd = open(argv[1], O_RDONLY);
	parse_scene(&env.scene, env.fd);
	init_scene(&env);
	if (!(env.scene.cam.z_buffer = malloc(env.scene.scrn.x * sizeof(double))))
		exit_message_failure(10);
	draw_env(&(env.scene), &env);
	if (env.save == 1)
	{
		if (!save_img_to_bmp(env.scene.scrn.x, env.scene.scrn.y,
		env.mlx_img.data, env.mlx_img.bpp))
			exit_message_failure(9);
		exit_hook(&env);
	}
	mlx_do_loop(&env);
	return (0);
}
