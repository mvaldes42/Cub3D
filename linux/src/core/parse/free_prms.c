/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_prms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 11:36:18 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/21 16:03:58 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void			free_prms(char **ptr)
{
	int i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

int				is_rgb(int r, int g, int b)
{
	if ((!((r <= 255 && r >= 0) && (g <= 255 && g >= 0) &&
	(b <= 255 && b >= 0))))
		return (0);
	return (1);
}

void			init_col(t_scene *s)
{
	s->col[0] = (t_rgb){300, 300, 300};
	s->col[1] = (t_rgb){300, 300, 300};
}
