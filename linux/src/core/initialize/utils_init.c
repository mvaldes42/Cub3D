/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 15:38:51 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/25 12:03:37 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialize.h"

float	v_length(t_point vector)
{
	return (sqrt((vector.x * vector.x) + (vector.y * vector.y)));
}

void	window_resize(t_env *env, t_scene *s_p)
{
	int x;
	int y;

	mlx_get_screen_size(env->mlx_ptr, &x, &y);
	s_p->scrn.x = s_p->scrn.x > x ? x : s_p->scrn.x;
	s_p->scrn.y = s_p->scrn.y > y ? y : s_p->scrn.y;
}
