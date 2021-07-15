PHILO_SRCS =	./philo.c \
				../aux/ft_atoi.c \
				../aux/ft_isdigit.c \
				../aux/time_diff.c \
				../parser/parser.c \
				./eat.c \
				./think.c \
				./sleep.c \
				./log.c

PHILO_OBJS = ${PHILO_SRCS:.c=.o}

NAME = philo_one

SANITIZE = -g3 -fsanitize=address

all: $(NAME)

bonus: $(BONUS_NAME)

philo_one: $(PHILO_OBJS)
	gcc $(PHILO_OBJS) -o $(NAME)

clean:
	rm -rf $(PHILO_OBJS)

fclean: clean
	rm -rf philo

re: clean fclean
	all