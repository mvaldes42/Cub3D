/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:11:43 by mvaldes           #+#    #+#             */
/*   Updated: 2020/07/29 13:46:28 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int argc, char *argv[])
{
	t_env		env;

	(void)argc;
	ft_bzero(&env, sizeof(env));
	init_scene(argv, &(env.scene));
	init_mlx(&env);
	draw_env(&(env.scene), &env);
	mlx_hook(env.mlx_win, X_EVENT_KEY_PRESS, 0, &key_press, &env);
	mlx_hook(env.mlx_win, X_EVENT_EXIT, 0, &exit_hook, &env);
	mlx_loop(env.mlx_ptr);
	return (0);
}
