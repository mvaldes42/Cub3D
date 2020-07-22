/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_resize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 17:23:34 by mvaldes           #+#    #+#             */
/*   Updated: 2020/07/22 18:29:13 by mvaldes          é###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void window_resize(t_scene *s_p)
{
	s_p->screen.x =  s_p->screen.x > DISP_X ? DISP_X : s_p->screen.x;
	s_p->screen.y =  s_p->screen.y > DISP_Y ? DISP_Y : s_p->screen.y;
}
