NAME = microRT

SRCS = collisions.c main.c shapes.c

CFLAGS = -Wall -Wextra -Werror -lSDL2 -lm

OBJS=$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@cc $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Ready to use ..."

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all re fclean clean 