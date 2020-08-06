/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 21:52:03 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/06 22:48:31 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __BMP_H
# define __BMP_H
# include "../../libraries/libft/libft.h"
# include <fcntl.h>

typedef struct	s_bmp_f_header
{
	unsigned char	bitmap_type[2];
	int				file_size;
	short int		reserved1;
	short int		reserved2;
	unsigned int	offset_bits;
}				t_bmp_f_header;

typedef	struct	s_bmp_h_header
{
	unsigned int	size_header;
	unsigned int	width;
	unsigned int	height;
	short int		planes;
	short int		bit_count;
	unsigned int	compression;
	unsigned int	image_size;
	unsigned int	ppm_x;
	unsigned int	ppm_y;
	unsigned int	clr_used;
	unsigned int	clr_important;
}				t_bmp_h_header;

typedef struct	s_bmp_img
{
	t_bmp_f_header	f_hdr;
	t_bmp_h_header	hdr;
}				t_bmp_img;

int				save_img_to_bmp(int screen_x, int screen_y, int line_l,
				char *img_data);

#endif
