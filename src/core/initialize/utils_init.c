/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 15:38:51 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/10 15:40:21 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialize.h"

float	v_length(t_point vector)
{
	return (sqrt((vector.x * vector.x) + (vector.y * vector.y)));
}

void	window_resize(t_scene *s_p)
{
	s_p->scrn.x = s_p->scrn.x > DISP_X ? DISP_X : s_p->scrn.x;
	s_p->scrn.y = s_p->scrn.y > DISP_Y ? DISP_Y : s_p->scrn.y;
}
