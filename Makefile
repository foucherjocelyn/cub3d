SRCS	= srcs/ray_casting.c srcs/main.c srcs/init.c

OBJS	= $(SRCS:.c=.o)

NAME	= cub3d

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
