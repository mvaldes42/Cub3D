/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 10:36:58 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/10 15:40:19 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __INITIALIZE_H
# define __INITIALIZE_H
# include "../cub3d.h"
# include "../parse/parse.h"
# include "../render/render.h"
# include <math.h>
# define DISP_X					2560
# define DISP_Y					1440

void			init_scene(t_env *env_p);
float			v_length(t_point vector);
void			window_resize(t_scene *s_p);

#endif
