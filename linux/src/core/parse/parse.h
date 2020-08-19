/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 21:18:17 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/19 21:50:07 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PARSE_H
# define __PARSE_H
# include "../cub3d.h"

int				parse_map(char **map, t_scene *s);
int				is_map_closed(char **map_a, t_scene *s);
void		    parse_scene(t_env *e, t_scene *s, char *argv[]);
void			parse_env_params(char *f_line, t_scene *scn);
void			free_prms(char **ptr);

#endif
