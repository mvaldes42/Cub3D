/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 21:52:03 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/21 18:03:09 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __BMP_H
# define __BMP_H
# include "../../libraries/libft/libft.h"
# include <fcntl.h>
# include "../cub3d.h"

int 	save_img_to_bmp(int screen_x, int screen_y, char *img_data,
					int bpp, t_env *e);

#endif
