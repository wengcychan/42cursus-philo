NAME = philo

SRCS = philo.c \
		init.c \
		utils.c \
		monitor.c

CC = cc

FLAGS = -Wall -Wextra -Werror -pthread
DEBUG = -fsanitize=thread -g

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $(OBJS) $(FLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

.PHONY: clean fclean re

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

debug:
	$(CC) -o $@ $(OBJS) $(FLAGS) $(DEBUG)