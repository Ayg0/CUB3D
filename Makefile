CC = cc

NAME = cub3d

CFLAGS = -Wall -Werror -Wextra -Imlx -g 
LFLAGS = -lmlx -framework OpenGl -framework Appkit -fsanitize=address

SRCS = cub3d.c genrl.c read_map.c init_data.c get_dx_dy.c check_h_v.c

OBJS = ${SRCS:.c=.o}

RM = rm -f

.c.o:
		$(CC) $(CFLAGS) -c -o $@ $<


all: $(NAME)

$(NAME):	$(OBJS)
		$(CC) $(LFLAGS) $(OBJS) -o $(NAME)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re