/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_resize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 16:46:27 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/06 21:37:42 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	window_resize(t_scene *s_p)
{
	s_p->screen.x = s_p->screen.x > DISP_X ? DISP_X : s_p->screen.x;
	s_p->screen.y = s_p->screen.y > DISP_Y ? DISP_Y : s_p->screen.y;
}
