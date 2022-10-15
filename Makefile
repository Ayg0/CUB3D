CC = cc

NAME = cub3d

CFLAGS = -Wall -Werror -Wextra -Imlx -g
LFLAGS = -lmlx -framework OpenGl -framework Appkit -fsanitize=address

SRCS = my_put.c genrl.c read_map.c

OBJS = ${SRCS:.c=.o}


.c.o:
		$(CC) $(CFLAGS) -c -o $@ $<

RM = rm -f

all: $(NAME)

$(NAME):	$(OBJS)
		$(CC) $(LFLAGS) $(OBJS) -o $(NAME)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re