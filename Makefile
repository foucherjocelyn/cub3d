SRCS	= srcs/ray_casting.c srcs/main.c srcs/init.c srcs/parsing.c srcs/ft_strcpy.c srcs/get_next_line/get_next_line.c srcs/get_next_line/get_next_line_utils.c srcs/atoi.c srcs/parsing_map.c srcs/sprite_casting.c srcs/rendering.c srcs/input.c srcs/draw_line.c srcs/errors.c srcs/init_parsing.c srcs/check_map.c srcs/ft_strcmp.c srcs/save.c

OBJS	= $(SRCS:.c=.o)

NAME	= cub3D

CC		= clang-9 

CFLAGS	= -Wall -Werror -Wextra -g3 -O0 -fsanitize=address

RM		= rm -f

%.o : %.c
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lmlx -lXext -lX11 -lm -lbsd


all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
