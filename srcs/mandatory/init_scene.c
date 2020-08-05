/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 13:36:31 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/05 13:22:11 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	v_length(t_point vector)
{
	return (sqrt((vector.x * vector.x) + (vector.y * vector.y)));
}

static int		load_xpm_texture(t_env *env, t_texture *text)
{
	if (text->path)
	{
		if ((text->img.addr = mlx_xpm_file_to_image(env->mlx_ptr, text->path,
							&text->width, &text->height)))
			text->img.data = mlx_get_data_addr(text->img.addr, &text->img.bpp,
							&text->img.line_len, &text->img.endian);
		else
			return(0);
	}
	return (1);
}

static void		load_game_textures(t_env *env_p, t_scene *scene_p)
{
	int i;

	i = 0;
	while (i < 5)
	{
		if (!load_xpm_texture(env_p, &(scene_p->env_text[i])))
				exit_message_failure();
		i++;
	}
}

void			init_mlx(t_env *env)
{
	g_error = 8;
	if ((!(env->mlx_ptr = mlx_init())) ||
	(!(env->mlx_win = mlx_new_window(env->mlx_ptr, env->scene.screen.x,
	env->scene.screen.y, GAME_NAME))))
		exit_message_failure();
	if (!(env->mlx_img.addr = mlx_new_image(env->mlx_ptr, env->scene.screen.x,
	env->scene.screen.y)) ||
	!(env->mlx_img.data = mlx_get_data_addr(env->mlx_img.addr,
	&env->mlx_img.bpp, &env->mlx_img.line_len, &env->mlx_img.endian)))
		exit_message_failure();
	load_game_textures(env, &(env->scene));
}

static void		init_camera(t_scene *scene_p)
{
	ft_bzero(&(scene_p->cam.pln_dir), sizeof(scene_p->cam.pln_dir));
	scene_p->cam.cam_fov = 66;
	scene_p->cam.pln_dir.x = scene_p->player.dir.y * 0.66 / 1;
	scene_p->cam.pln_dir.y = (-scene_p->player.dir.x) * 0.66 / 1;
	if (scene_p->cam.pln_dir.y == 0)
		scene_p->cam.pln_dir.y = 0;
	if (scene_p->cam.pln_dir.x == 0)
		scene_p->cam.pln_dir.x = 0;
	scene_p->cam.pln_len = v_length(scene_p->cam.pln_dir) * 2;
	scene_p->cam.dir_len = v_length(scene_p->player.dir);
}

void			init_scene(char **argv, t_scene *scene_p)
{
	ft_bzero(&scene_p->player, sizeof(scene_p->player));
	ft_bzero(&scene_p->cam, sizeof(scene_p->cam));
	ft_bzero(&scene_p->env_text, sizeof(scene_p->env_text));
	int i = 0;
	while (i < 5)
	{
		ft_bzero(&scene_p->env_text[i], sizeof(scene_p->env_text[i]));
		i++;
	}
	parse_scene(scene_p, open(argv[1], O_RDONLY));
	scene_p->player.pos.x += 0.5;
	scene_p ->player.pos.y += 0.5;
	window_resize(scene_p);
	init_camera(scene_p);
}

/*
**	scene_p->cam.pln_len = scene_p->screen.x;
**	scene_p->cam.dir_len = (scene_p->cam.pln_len / 2) /
**	tan(scene_p->cam.cam_fov / 2 * (M_PI / 180));
**	scene_p->cam.dir_len = 1662;
**	scene_p->cam.angleRays = (float)scene_p->cam.cam_fov /
**	(float)scene_p->cam.pln_len;
**	scene_p->cam.cam_fov = (atan((float)(scene_p->cam.pln_len / 2) /
**	(float)scene_p->cam.dir_len)) * 2 * (180 / M_PI);
*/
