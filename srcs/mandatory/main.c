/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:11:43 by mvaldes           #+#    #+#             */
/*   Updated: 2020/04/30 17:29:49 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int argc, char *argv[])
{
	t_scene		scene;
	int			fd;
	data_t		data;

	(void)argc;
	fd = open(argv[1], O_RDONLY);
	ft_bzero(&scene, sizeof(scene));
	scene = parse_scene(scene, fd);
/*
** 	printf("screen x = %d && screen y = %d\n", scene.screen.x, scene.screen.y);
** 	printf("north text = %s\n", scene.n_tex);
** 	printf("r = %d & g = %d & b = %d \n", scene.flr_clr.r, scene.flr_clr.g, scene.flr_clr.b);
** 	printf("size map = %d\n", ft_lstsize_map(scene.map));
** 	print(scene.map);
*/
	if ((data.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((data.mlx_win = mlx_new_window(data.mlx_ptr, 1920, 1080, "Hello world")) == NULL)
		return (EXIT_FAILURE);
	mlx_pixel_put(data.mlx_ptr, data.mlx_win, 1920/2, 1080/2, 0xFFCCCC);
	mlx_string_put(data.mlx_ptr, data.mlx_win, 1920/2, 1080/2, 0xFFCCCC, "HELLO WORLD");
	mlx_loop(data.mlx_ptr);
	return (EXIT_SUCCESS);
}
