NAME = try_to_beat_me

SRCS = 	src/ai.c \
		src/game.c \
		src/main.c \
		src/map.c \
		src/print.c 

CFLAGS = -Iinclude -O3

OBJS = $(SRCS:.c=.o)

$(NAME):	$(OBJS)
			gcc $(CFLAGS) $(OBJS) -o $(NAME) -lcsfml-graphics -lcsfml-window -lcsfml-system



re:			fclean $(NAME)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)
