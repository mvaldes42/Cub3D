# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/15 14:41:36 by mvaldes           #+#    #+#              #
#    Updated: 2020/08/20 16:12:04 by mvaldes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: libft minilibx-linux

SRCS =	./src/core/main.c\
		./src/core/utils_general.c\
		./src/core/parse/parse_map.c\
		./src/core/parse/parse_scene.c\
		./src/core/parse/parse_params.c\
		./src/core/parse/map_lst.c\
		./src/core/parse/free_prms.c\
		./src/core/initialize/init_scene.c\
		./src/core/initialize/utils_init.c\
		./src/core/render/window_draw.c\
		./src/core/render/draw_sprite.c\
		./src/core/render/digital_diff_analy.c\
		./src/core/render/utils_color.c\
		./src/core/snapshot/save_bmp.c\
		./src/core/move/hooks.c\
		./src/core/move/player_move.c\
		./src/libraries/get_next_line/get_next_line.c\
		./src/libraries/get_next_line/get_next_line_utils.c\

NAME = Cub3D
CC_FLAG = -Wall -Werror -Wextra
CC = clang $(CC_FLAG)
LIBFT = src/libraries/libft
MLX = src/libraries/minilibx-linux

OBJS = $(SRCS:.c=.o)

all: libft minilibx-linux $(NAME)
libft:
	make -C $(LIBFT)

minilibx-linux:
	make -C $(MLX)

$(%.o): $(%.c)
	$(CC) -I/usr/include -Imlx_linux -O3 -o $@ -c $^

$(NAME): $(OBJS)
	$(CC) -o $@ $^ -L. -L$(LIBFT) -L$(MLX) -lft -lmlx -lXext -lX11 -lm
clean:
	rm -f $(OBJS)
	make -C $(LIBFT) clean
	make -C $(MLX) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT) fclean
	make -C $(MLX) clean

re: fclean all
