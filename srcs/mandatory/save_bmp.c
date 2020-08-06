/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 16:04:35 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/06 19:05:57 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	save_img_to_bmp(t_env *env, t_scene *scene)
{
	t_bmp_img	bmp;
	char		*file_name;
	int			i;
	int			fd;

	file_name = "cub3d_snapshot.bmp";
	ft_memcpy(&bmp.f_hdr.bitmap_type, "BM", 2);
	bmp.f_hdr.file_size = 54 + 4 * scene->screen.x * scene->screen.y;
	bmp.f_hdr.reserved1 = 0;
	bmp.f_hdr.reserved2 = 0;
	bmp.f_hdr.offset_bits = 0;

	bmp.hdr.size_header = 40;
	bmp.hdr.width = scene->screen.x;
	bmp.hdr.height = scene->screen.y;
	bmp.hdr.planes = 1;
	bmp.hdr.bit_count = 32;
	bmp.hdr.compression = 0;
	bmp.hdr.image_size = scene->screen.x * scene->screen.y;
	bmp.hdr.ppm_x = 0;
	bmp.hdr.ppm_y = 0;
	bmp.hdr.clr_used = 0;
	bmp.hdr.clr_important = 0;

	if ((fd = open(file_name, O_RDWR | O_CREAT, S_IRWXU | O_TRUNC)) < 0)
		exit_message_failure();
	write(fd, &(bmp.f_hdr), 14);
	write(fd, &(bmp.hdr), 40);
	i = scene->screen.y + 1;
	int bmp_line_size = scene->screen.x * 4;
	while (--i >= 0)
		write(fd, &env->mlx_img.data[i * (env->mlx_img.line_len)], bmp_line_size);
	close(fd);
}

void	take_game_snapshot(t_env *env)
{
	save_img_to_bmp(env, &env->scene);
	exit_hook(env);
}
