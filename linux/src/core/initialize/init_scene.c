/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 13:36:31 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/12 23:12:39 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialize.h"

static void		load_game_textures(t_env *env, t_scene *scene)
{
	int			i;
	t_texture	*text;

	i = 0;
	while (i < 5)
	{
		text = &(scene->tex[i]);
		if ((text->img.addr = mlx_xpm_file_to_image(env->mlx_ptr, text->path,
		&text->w, &text->h)))
			text->img.data = mlx_get_data_addr(text->img.addr, &text->img.bpp,
			&text->img.line_len, &text->img.endian);
		else
			exit_message_failure(9);
		i++;
	}
}

static void		init_mlx(t_env *env)
{
	if ((!(env->mlx_ptr = mlx_init())))
		exit_message_failure(8);
	if (env->save == 0)
	{
		window_resize(env, &env->scene);
		if (!(env->mlx_win = mlx_new_window(env->mlx_ptr, env->scene.scrn.x,
		env->scene.scrn.y, GAME_NAME)))
			exit_message_failure(8);
	}
	if (!(env->mlx_img.addr = mlx_new_image(env->mlx_ptr, env->scene.scrn.x,
	env->scene.scrn.y)) || !(env->mlx_img.data =
	mlx_get_data_addr(env->mlx_img.addr, &env->mlx_img.bpp,
	&env->mlx_img.line_len, &env->mlx_img.endian)))
		exit_message_failure(8);
	load_game_textures(env, &(env->scene));
}

static void		init_camera(t_scene *scene)
{
	scene->cam.cam_fov = 66;
	scene->cam.pln.x = scene->plyr.dir.y * 0.66 / 1;
	scene->cam.pln.y = (-scene->plyr.dir.x) * 0.66 / 1;
	if (scene->cam.pln.y == 0)
		scene->cam.pln.y = 0;
	if (scene->cam.pln.x == 0)
		scene->cam.pln.x = 0;
	scene->cam.pln_len = v_length(scene->cam.pln) * 2;
	scene->cam.dir_len = v_length(scene->plyr.dir);
}

static void		init_sprites(t_scene *scene)
{
	int i;
	int j;
	int count;

	scene->sprt.pos = malloc(scene->sprt.nbr * sizeof(t_point));
	i = 0;
	count = 0;
	while (i < ft_lstsize_map(scene->map))
	{
		j = 0;
		while (scene->map_a[i][j] && count < scene->sprt.nbr)
		{
			if (ft_strrchr("2", scene->map_a[i][j]))
			{
				scene->sprt.pos[count].x = i + 0.5;
				scene->sprt.pos[count].y = j + 0.5;
				count++;
			}
			j++;
		}
		i++;
	}
}

void			init_scene(t_env *env)
{
	init_camera(&env->scene);
	init_sprites(&env->scene);
	init_mlx(env);
}
