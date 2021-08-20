PHILO_SRCS =	./philo.c \
				./eat.c \
				./think.c \
				./sleep.c \
				./thread.c \
				./philo_init.c \
				./monitor.c \
				./aux/ft_atoi.c \
				./aux/ft_isdigit.c \
				./aux/time_diff.c \
				./aux/ft_msleep.c \
				./parser/parser.c \
				./log/log.c


PHILO_OBJS = ${PHILO_SRCS:.c=.o}

NAME = philo
CFLAGS= -Wall -Werror -Wextra

all: $(NAME)

philo: $(PHILO_OBJS)
	gcc $(PHILO_OBJS) -o $(NAME) -pthread

clean:
	rm -rf $(PHILO_OBJS)

fclean: clean
	rm -rf philo

re: fclean all
