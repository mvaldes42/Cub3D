# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/15 14:41:36 by mvaldes           #+#    #+#              #
#    Updated: 2020/08/12 19:22:07 by mvaldes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: libft minilibx

SRCS =	./src/core/main.c\
		./src/core/utils_general.c\
		./src/core/parse/parse_map.c\
		./src/core/parse/parse_scene.c\
		./src/core/parse/parse_params.c\
		./src/core/parse/map_lst.c\
		./src/core/parse/utils_lst.c\
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

NAME = cub3D
GCC_FLAG = -Wall -Werror -Wextra -g
CC = gcc $(GCC_FLAG)
LIBFT = src/libraries/libft
MLX = src/libraries/minilibx/

OBJS = $(SRCS:.c=.o)

all: libft minilibx $(NAME)

libft:
	make -C $(LIBFT)

minilibx:
	make -C $(MLX)

$(%.o): $(%.c)
	$(CC) -o $@ -c $^

$(NAME): $(OBJS)
	$(CC) -o $@ $^ -L$(LIBFT) -lft -L$(MLX) -lmlx -framework OPENGL -framework Appkit
	# -fsanitize=address
clean:
	rm -f $(OBJS)
	make -C $(LIBFT) clean
	make -C $(MLX) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT) fclean
	make -C $(MLX) clean

re: fclean all
