/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:11:43 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/11 13:35:20 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "initialize/initialize.h"
#include "./snapshot/bmp.h"

int		main(int argc, char *argv[])
{
	t_env		env;

	(void)argc;
	ft_bzero(&env, sizeof(env));
	env.fd = open(argv[1], O_RDONLY);
	parse_scene(&env.scene, env.fd);
	init_scene(&env, argv);
	if (!(env.scene.cam.z_buffer = malloc(env.scene.scrn.x * sizeof(double))))
		exit_message_failure(10);
	draw_env(&(env.scene), &env);
	if (ft_strnstr(argv[2], "--save", ft_strlen(argv[2])))
	{
		if (!save_img_to_bmp(env.scene.scrn.x, env.scene.scrn.y,
		env.mlx_img.line_len, env.mlx_img.data))
			exit_message_failure(9);
		exit_hook(&env);
	}
	mlx_hook(env.mlx_win, X_EVENT_KEY_PRESS, 0, &key_press, &env);
	mlx_hook(env.mlx_win, X_EVENT_EXIT, 0, &exit_hook, &env);
	mlx_loop(env.mlx_ptr);
	return (0);
}

	// printf("scene_p->plyr.pos.x : %f\n", env.scene.plyr.pos.x);
	// printf("scene_p->plyr.pos.y : %f\n", env.scene.plyr.pos.y);
	// printf("scene_ptr->plyr.dir.x : %f\n", env.scene.plyr.dir.x);
	// printf("scene_ptr->plyr.dir.y : %f\n", env.scene.plyr.dir.y);
	// printf("scene_ptr->cam.pln_dir.x : %f\n", env.scene.cam.pln_dir.x);
	// printf("scene_ptr->cam.pln_dir.y : %f\n", env.scene.cam.pln_dir.y);
	// printf("scene_ptr->cam.pln_len : %f\n", env.scene.cam.pln_len);
	// printf("scene_ptr->cam.dir_len  : %f\n", env.scene.cam.dir_len);
