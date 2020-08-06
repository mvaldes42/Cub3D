/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 23:02:13 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/06 23:04:10 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MOVE_H
# define __MOVE_H
# include "../cub3d.h"
# define KEY_Q					12
# define KEY_E					14
# define KEY_LEFT				123
# define KEY_RIGHT				124
# define KEY_ESC				53
# define KEY_W					13
# define KEY_A					0
# define KEY_S					1
# define KEY_D					2

void			rotate(t_scene *scene_p, int f);
void			move(t_scene *scene_p, char f);
void			translate(t_scene *scene_p, char f);

#endif
