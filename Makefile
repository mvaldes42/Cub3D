# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/15 14:41:36 by mvaldes           #+#    #+#              #
#    Updated: 2020/08/05 15:27:42 by mvaldes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: libft minilibx

SRCS = ./srcs/mandatory/utils_lst.c\
	   ./srcs/mandatory/utils_general.c\
	   ./srcs/mandatory/utils_color.c\
	   ./srcs/mandatory/init_scene.c\
	   ./srcs/mandatory/parse_scene.c\
	   ./srcs/mandatory/parse_params.c\
	   ./srcs/mandatory/parse_map.c\
	   ./srcs/mandatory/map_lst.c\
	   ./srcs/mandatory/window_draw.c\
	   ./srcs/mandatory/window_resize.c\
	   ./srcs/mandatory/digital_diff_analy.c\
	   ./srcs/mandatory/player_move.c\
	    ./srcs/mandatory/hooks.c\
	   ./srcs/mandatory/main.c\
	   ./srcs/get_next_line/get_next_line.c\
	   ./srcs/get_next_line/get_next_line_utils.c\

NAME = Cub3D
GCC_FLAG = -Wall -Werror -Wextra -g
CC = gcc $(GCC_FLAG)

OBJS = $(SRCS:.c=.o)

all: libft minilibx $(NAME)

libft:
	make -C srcs/libft/

minilibx:
	make -C srcs/minilibx/

$(%.o): $(%.c)
	$(CC) -o $@ -c $^

$(NAME): $(OBJS)
	$(CC) -o $@ $^ -Lsrcs/libft -lft -Lsrcs/minilibx/ -lmlx -framework OPENGL -framework Appkit
clean:
	rm -f $(OBJS)
	make -C srcs/libft/ clean
	make -C srcs/minilibx/ clean

fclean: clean
	rm -f $(NAME)
	make -C srcs/libft/ fclean
	make -C srcs/minilibx/ clean

re: fclean all
