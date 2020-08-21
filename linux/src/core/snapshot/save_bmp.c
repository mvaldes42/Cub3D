/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 16:04:35 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/21 19:05:51 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"

static char		*init_bmp_header(int *screen, char *head)
{
	ft_bzero(head, 54);
	head[0] = 'B';
	head[1] = 'M';
	head[2] = (unsigned char)(54 + 4 * screen[0] * screen[1]);
	head[3] = (unsigned char)((54 + 4 * screen[0] * screen[1]) >> 8);
	head[4] = (unsigned char)((54 + 4 * screen[0] * screen[1]) >> 16);
	head[5] = (unsigned char)((54 + 4 * screen[0] * screen[1]) >> 24);
	head[10] = 54;
	head[14] = 40;
	head[18] = (unsigned char)screen[0];
	head[19] = (unsigned char)(screen[0] >> 8);
	head[20] = (unsigned char)(screen[0] >> 16);
	head[21] = (unsigned char)(screen[0] >> 24);
	head[22] = (unsigned char)screen[1];
	head[23] = (unsigned char)(screen[1] >> 8);
	head[24] = (unsigned char)(screen[1] >> 16);
	head[25] = (unsigned char)(screen[1] >> 24);
	head[26] = 1;
	head[28] = 32;
	return (head);
}

static char		*invert_line(char *img, t_env *e)
{
	char	*invert;
	int		i;
	int		j;
	(void)e;
	(void)img;
	char *test = "0123abcd";

	invert = malloc(ft_strlen(test) * sizeof(char));
	int len = ft_strlen(test);
	i = 0;
	j = 0;
	while (i + j< len)
	{
		j = 0;
		while (j < 4)
		{
			invert[i + j] = test[ len - 4 * (i+1)];
			printf("%c\n", invert[i +j]);
			j++;
		}
		i++;
	}
	printf("-%s-\n", invert);
	return (invert);
}

static int		write_to_bmp(int *screen, char *img_data, int bpp, t_env *e)
{
	int			i;
	int			fd;
	char		*head;
	char *tmp;

	if (!(fd = open("cub3d_snapshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0755)))
		return (0);
	if (!(head = malloc(sizeof(char) * 54)))
		return (0);
	head = init_bmp_header(screen, head);
	write(fd, head, 54);
	free(head);
	tmp = invert_line(img_data, e);

	i = screen[1] * screen[0] - 1;
	while (i >= 0)
	{
		write(fd, &img_data[i * bpp / 8], 4);
		i--;
	}

	close(fd);
	return (1);
}

int				save_img_to_bmp(int screen_x, int screen_y, char *img_data,
				int bpp, t_env *e)
{
	int			*screen;

	screen = (int[2]) {screen_x, screen_y};
	if (!write_to_bmp(screen, img_data, bpp, e))
		return (0);
	return (1);
}
