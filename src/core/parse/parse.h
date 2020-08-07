/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 21:18:17 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/07 10:54:27 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PARSE_H
# define __PARSE_H
# include "../cub3d.h"

int				parse_map(char **map);
int				is_map_closed(char **map_a);
void			parse_scene(t_scene *scene_ptr, int fd);
void			parse_env_params(char *f_line, t_scene *scn);

#endif
