/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 13:51:21 by mvaldes           #+#    #+#             */
/*   Updated: 2020/08/07 10:51:36 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CUB3D_H
# define __CUB3D_H
# include <fcntl.h>//OPEN
# include <stdio.h>//PRINTF
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
	t_point	pln_dir;
	double	pln_len;
	double	dir_len;
	double	cam_fov;
}				t_camera;

typedef	struct	s_player
{
	t_point	pos;
	t_point	dir;
}				t_player;

typedef	struct	s_screen
{
	int	x;
	int	y;
}				t_screen;

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
	int			width;
	int			height;
	double		step;
	double		texel_pos;
}				t_texture;

typedef struct	s_scene
{
	t_screen	screen;
	t_map		*map;
	char		**map_a;
	t_player	player;
	t_camera	cam;
	t_texture	env_text[5];
	t_rgb		env_col[2];

}				t_scene;

typedef struct	s_env
{
	void	*mlx_ptr;
	void	*mlx_win;
	t_data	mlx_img;
	t_scene	scene;
}				t_env;

void			print_map(t_map *map);

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
