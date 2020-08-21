/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 21:18:17 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/21 16:04:12 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PARSE_H
# define __PARSE_H
# include "../cub3d.h"

int				parse_map(t_env *e, char **map, t_scene *s);
int				is_map_closed(char **map_a, t_scene *s);
void			parse_scene(t_env *e, t_scene *s, char *argv[]);
void			parse_env_params(t_env *e, char *f_line, t_scene *scene_p);
void			free_prms(char **ptr);
int				is_rgb(int r, int g, int b);
void			init_col(t_scene *s);

#endif
