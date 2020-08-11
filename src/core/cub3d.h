/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 13:51:21 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/11 13:32:41 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CUB3D_H
# define __CUB3D_H
# include <fcntl.h>
#include <stdio.h>
# include "../libraries/get_next_line/get_next_line.h"
# include "../libraries/libft/libft.h"
# include "../libraries/minilibx/mlx.h"
# include "error.h"

# define GAME_NAME				"Cub3D"
# define X_EVENT_EXIT			17
# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3

typedef struct	s_point
{
	double	x;
	double	y;
}				t_point;

typedef	struct	s_point_i
{
	int	x;
	int	y;
}				t_point_i;

typedef struct	s_point_ll
{
	long long x;
	long long y;
}				t_point_ll;

typedef	struct	s_rgb
{
	int	r;
	int	g;
	int	b;
}				t_rgb;

typedef struct	s_map
{
	char			*line;
	struct s_map	*next;
}				t_map;

typedef	struct	s_camera
{
	t_point	pln;
	double	pln_len;
	double	dir_len;
	double	cam_fov;
	double	*z_buffer;
}				t_camera;

typedef	struct	s_player
{
	t_point	pos;
	t_point	dir;
}				t_player;

typedef struct	s_data
{
	void	*addr;
	char	*data;
	int		bpp;
	int		line_len;
	int		endian;
}				t_data;

typedef struct	s_texture
{
	char		*path;
	t_data		img;
	int			w;
	int			h;
	double		step;
	double		texel_pos;
}				t_texture;

typedef struct	s_sprite
{
	int			nbr;
	t_point		*pos;
	t_point		r_pos;
	double		*dst;
	double		inv_det;
	t_point		trsfrm;
	int			s_scrn_x;
	t_point_i	dim;
	t_point_i	start;
	t_point_i	end;
	t_point_i	textr;
	int			d;
	int			clr;

}				t_sprite;

typedef struct	s_scene
{
	t_point_ll	scrn;
	t_map		*map;
	char		**map_a;
	t_player	plyr;
	t_camera	cam;
	t_texture	tex[5];
	t_rgb		col[2];
	t_sprite	sprt;

}				t_scene;

typedef struct	s_env
{
	void	*mlx_ptr;
	void	*mlx_win;
	t_data	mlx_img;
	t_scene	scene;
	int		fd;
}				t_env;

void			print_map(t_map *map);
int				ft_isnum(char *str);

t_map			*ft_lstnew_map(char *line);
t_map			*ft_lstlast_map(t_map *lst);
void			ft_lstadd_back_map(t_map **alst, t_map *new);
void			ft_lstclear_map(t_map **lst);
int				ft_lstsize_map(t_map *lst);

void			cvt_lst_to_array(t_scene *scene_ptr, char *f_line, int fd,
				int ret);

void			draw_env(t_scene *scene_p, t_env *env_p);

int				key_press(int keycode, t_env *env);
int				exit_hook(t_env *env);

#endif
