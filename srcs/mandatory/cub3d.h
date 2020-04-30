/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 13:51:21 by mvaldes           #+#    #+#             */
/*   Updated: 2020/04/30 15:21:14 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CUB3D_H
# define __CUB3D_H
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "../minilibx/mlx.h"

typedef struct	data_s
{
	void		*mlx_ptr;
	void		*mlx_win;
}				data_t;

typedef struct	s_map
{
	char			*line;
	struct s_map	*next;
}				t_map;

typedef	struct	s_screen
{
	int			x;
	int			y;
}				t_screen;

typedef	struct	s_rgb
{
	int			r;
	int			g;
	int			b;
}				t_rgb;

typedef	struct	s_player
{
	int			x;
	int			y;
	char		orientation;
}				t_player;

typedef struct	s_scene
{
	t_screen	screen;
	char		*n_tex;
	char		*s_tex;
	char		*e_tex;
	char		*w_tex;
	char		*sprt_tex;
	t_rgb		flr_clr;
	t_rgb		cei_clr;
	t_map		*map;
	char		**map_a;
	t_player	player;

}				t_scene;

typedef enum	e_error
{
	E_UNK_ERROR = 0,
	E_NOT_ENOUGH_ARG = 1,
	E_UNK_ARG = 2,
	E_LST_MAP = 3,
	E_INV_FILE_SYNT = 4,
	E_RBG_SYNT = 5,
	E_MAP_N_CLS = 6,
	E_MAP_I_CHAR = 7,
}				t_error;

typedef struct	s_errordesc
{
	int		code;
	char	*msg;
}				t_errordesc;

static const	t_errordesc g_errorm[] =
{
	{E_UNK_ERROR, "Unknown error."},
	{E_NOT_ENOUGH_ARG, "Not enough arguments in scene.cub file."},
	{E_UNK_ARG, "Unknown argument in scene.cub file."},
	{E_LST_MAP, "Could not create map linked list."},
	{E_INV_FILE_SYNT, "Invalid texture file synthax."},
	{E_RBG_SYNT, "Invalid RGB synthax."},
	{E_MAP_N_CLS, "Invalid map (map not closed)."},
	{E_MAP_I_CHAR, "Invalid map (invalid character)."},
};

int	g_error;

void			exit_message_failure(void);
void			print_map(t_map *map);

t_map			*ft_lstnew_map(char *line);
t_map			*ft_lstlast_map(t_map *lst);
void			ft_lstadd_back_map(t_map **alst, t_map *new);
void			ft_lstclear_map(t_map **lst);
int				ft_lstsize_map(t_map *lst);

char			**convert_lst_to_array(t_map *map);
t_map			*create_map_lst(t_scene scene, char *f_line, int fd, int ret);

int				parse_map(char **map);
int				is_map_closed(char **map_a);
t_scene			parse_scene(t_scene scene, int fd);
t_scene			parse_env_params(char *f_line, t_scene scn);

#endif
