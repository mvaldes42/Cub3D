/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 16:04:35 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/06 22:46:24 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"
#include <stdio.h>

static void		init_bmp_header(t_bmp_img *bmp, int *screen)
{
	ft_bzero(bmp, sizeof(*bmp));
	ft_memcpy(bmp->f_hdr.bitmap_type, "BM", 2);
	bmp->f_hdr.file_size = 54 + 4 * screen[0] * screen[1];
	bmp->hdr.size_header = 40;
	bmp->hdr.width = screen[0];
	bmp->hdr.height = screen[1];
	bmp->hdr.planes = 1;
	bmp->hdr.bit_count = 32;
	bmp->hdr.image_size = screen[0] * screen[1];
}

static int		write_to_bmp(int *screen, int line_l,
				char *img_data, t_bmp_img *bmp)
{
	int			i;
	int			fd;

	if ((fd = open("cub3d_snapshot.bmp",
		O_RDWR | O_CREAT, S_IRWXU | O_TRUNC)) < 0)
		return (0);
	write(fd, &(bmp->f_hdr), 14);
	write(fd, &(bmp->hdr), 40);
	i = screen[1] + 1;
	while (--i >= 0)
		write(fd, &img_data[i * line_l], screen[0] * 4);
	close(fd);
	return (1);
}

int				save_img_to_bmp(int screen_x, int screen_y, int line_l,
				char *img_data)
{
	t_bmp_img	bmp;
	int			*screen;

	screen = (int[2]) {screen_x, screen_y};
	init_bmp_header(&bmp, screen);
	if (!write_to_bmp(screen, line_l, img_data, &bmp))
		return (0);
	return (1);
}
