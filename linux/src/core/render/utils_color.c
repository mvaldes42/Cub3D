/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 15:26:15 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/12 20:28:23 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int		create_trgb_shade(int t, t_rgb color, int d)
{
	if (d <= 1)
		return (t << 24 | color.r << 16 | color.g << 8 | color.b);
	return (t << 24 | (color.r / d << 16) | (color.g / d << 8) | color.b / d);
}
