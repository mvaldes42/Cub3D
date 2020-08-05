/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 16:04:35 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/05 16:30:02 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	save_img_to_bmp(t_scene *scene, t_env *env)
{
	(void)env;
	bfh			bfh;
	bih			bih;
	const char	*file_name;
	FILE		*img;
	int			img_size;
	int			file_size;
	int			dpi = 300;

	img_size = scene->screen.x * scene->screen.y;
	file_size = 54 + 4 * img_size;
	int ppm = dpi * 39.375;

	ft_memcpy(&bfh.bitmap_type, "BM", 2);
	bfh.file_size = file_size;
	bfh.reserved1 = 0;
	bfh.reserved2 = 0;
	bfh.offset_bits = 0;

	bih.size_header = sizeof(bih);
	bih.width = scene->screen.x;
	bih.height = scene->screen.y;
	bih.planes = 1;
	bih.bit_count = 24;
	bih.compression = 0;
	bih.image_size = file_size;
	bih.ppm_x = ppm;
	bih.ppm_y = ppm;
	bih.clr_used = 0;
	bih.clr_important = 0;
	img = fopen(file_name, "wb");
	fwrite(&bfh, 1, 14, img);
	fwrite(&bih, 1, sizeof(bih), img);
	for (int i = 0; i < img; i++)
	{
		t_rgb BGR = data[i];
		float red   = (BGR.r);
		float green = (BGR.g);
		float blue  = (BGR.b);
		unsigned char color[3] = { blue, green, red};
		fwrite(color, 1, sizeof(color), img);
	}
	fclose(img);
}
