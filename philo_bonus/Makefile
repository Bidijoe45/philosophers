PHILO_SRCS_BONUS =	./philo_bonus.c \
					./eat_bonus.c \
					./think_bonus.c \
					./sleep_bonus.c \
					./process_bonus.c \
					./philo_init_bonus.c \
					./monitor_bonus.c \
					./aux/ft_atoi.c \
					./aux/ft_isdigit.c \
					./aux/time_diff.c \
					./aux/ft_msleep.c \
					./parser/parser.c \
					./log/log_bonus.c

PHILO_BONUS_OBJS = ${PHILO_SRCS_BONUS:.c=.o}

BONUS_NAME = philo_bonus
CFLAGS= -Wall -Werror -Wextra
SANITIZE = -g3 -fsanitize=address

all: $(BONUS_NAME)

philo_bonus: $(PHILO_BONUS_OBJS)
	gcc $(PHILO_BONUS_OBJS) -o $(BONUS_NAME) -pthread

clean:
	rm -rf $(PHILO_BONUS_OBJS)

fclean: clean
	rm -rf philo_bonus

re: fclean all