/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 23:02:13 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/07 10:35:23 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MOVE_H
# define __MOVE_H
# include "../cub3d.h"
# include <math.h>
# define KEY_LEFT				65361
# define KEY_RIGHT				65363
# define KEY_ESC				65307
# define KEY_Z					122
# define KEY_D					100
# define KEY_S					115
# define KEY_Q					113

void			rotate(t_scene *scene_p, int f);
void			move(t_scene *scene_p, char f);
void			translate(t_scene *scene_p, char f);

#endif
