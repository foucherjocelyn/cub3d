SRCS	= srcs/ray_casting.c srcs/main.c srcs/init.c srcs/parsing.c srcs/ft_strcpy.c srcs/get_next_line/get_next_line.c srcs/get_next_line/get_next_line_utils.c srcs/atoi.c srcs/parsing_map.c srcs/sprite_casting.c srcs/rendering.c srcs/input.c srcs/draw_line.c srcs/errors.c srcs/init_parsing.c srcs/check_map.c srcs/ft_strcmp.c srcs/save.c srcs/ft_str_at_end.c

OBJS	= $(SRCS:.c=.o)

NAME	= cub3D

CC		= clang-9 

CFLAGS	= -Wall -Werror -Wextra -O3

RM	= rm -f

MLX_DIR	= minilibx-linux

%.o : %.c
		$(CC) $(CFLAGS) -c $< -o $@

all:		mlx $(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -I./$(MLX_DIR) -lbsd -lm -lX11 -lXext -L ./$(MLX_DIR) -lmlx -o $(NAME)


mlx:		
		$(MAKE) -C $(MLX_DIR)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)
			cd $(MLX_DIR) && make clean

re:			fclean all

.PHONY:		all clean fclean re mlx
