/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 10:58:01 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/25 11:53:19 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"

static char		*init_bmp_header(char *head, int screen_x, int screen_y)
{
	int file_size;

	ft_bzero(head, 54);
	file_size = 14 + 40 + 4 + (screen_x * screen_y) * 4;
	head[0] = 'B';
	head[1] = 'M';
	head[2] = (unsigned char)(file_size);
	head[3] = (unsigned char)((file_size) >> 8);
	head[4] = (unsigned char)((file_size) >> 16);
	head[5] = (unsigned char)((file_size) >> 24);
	head[10] = 14 + 40 + 4;
	head[14] = 40;
	head[18] = (unsigned char)screen_x;
	head[19] = (unsigned char)(screen_x >> 8);
	head[20] = (unsigned char)(screen_x >> 16);
	head[21] = (unsigned char)(screen_x >> 24);
	head[22] = (unsigned char)screen_y;
	head[23] = (unsigned char)(screen_y >> 8);
	head[24] = (unsigned char)(screen_y >> 16);
	head[25] = (unsigned char)(screen_y >> 24);
	head[26] = 1;
	head[28] = 32;
	return (head);
}

static void		swap_bytes(t_data *mlx_img, int l_nbr, int *byte, int pxl)
{
	char	tmp;
	int		byte_count;

	byte_count = 3;
	while (byte_count >= 0)
	{
		tmp = mlx_img->data[*byte + (l_nbr * mlx_img->line_len)];
		mlx_img->data[*byte + (l_nbr * mlx_img->line_len)] = mlx_img->data[pxl -
		byte_count + (l_nbr * mlx_img->line_len - 1)];
		mlx_img->data[pxl - byte_count + (l_nbr * mlx_img->line_len - 1)] = tmp;
		byte_count--;
		*byte += 1;
	}
}

static void		mirror_img(t_data *mlx_img, int screen_y)
{
	int		l_nbr;
	int		byte;
	int		pxl;

	l_nbr = -1;
	while (++l_nbr < screen_y)
	{
		byte = 0;
		pxl = mlx_img->line_len;
		while (byte < pxl)
		{
			swap_bytes(mlx_img, l_nbr, &byte, pxl);
			pxl -= 4;
		}
	}
}

int				save_img_to_bmp(int screen_x, int screen_y, t_data *mlx_img)
{
	int		fd;
	int		i;
	char	*head;

	if (!(fd = open("cub3d_snapshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0755)))
		return (0);
	if (!(head = malloc(sizeof(char) * 54)))
		return (0);
	head = init_bmp_header(head, screen_x, screen_y);
	write(fd, head, 54);
	free(head);
	mirror_img(mlx_img, screen_y);
	i = screen_x * screen_y - 2;
	while (--i >= 0)
		write(fd, &mlx_img->data[i * mlx_img->bpp / 8], 4);
	close(fd);
	return (1);
}
