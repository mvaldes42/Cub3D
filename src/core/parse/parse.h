/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 21:18:17 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/06 21:24:14 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PARSE_H
# define __PARSE_H

// typedef struct	s_map
// {
// 	char			*line;
// 	struct s_map	*next;
// }				t_map;

int				parse_map(char **map);
int				is_map_closed(char **map_a);
void			parse_scene(t_scene *scene_ptr, int fd);
void			parse_env_params(char *f_line, t_scene *scn);

#endif
