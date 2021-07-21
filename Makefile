PHILO_SRCS =	./srcs/philo_one/philo.c \
				./srcs/aux/ft_atoi.c \
				./srcs/aux/ft_isdigit.c \
				./srcs/aux/time_diff.c \
				./srcs/parser/parser.c \
				./srcs/philo_one/eat.c \
				./srcs/philo_one/think.c \
				./srcs/philo_one/sleep.c \
				./srcs/philo_one/log.c

PHILO_SRCS_BONUS =	./srcs/philo_bonus/philo_bonus.c \
					./srcs/aux/ft_atoi.c \
					./srcs/aux/ft_isdigit.c \
					./srcs/aux/time_diff.c \
					./srcs/parser/parser.c \
					./srcs/philo_bonus/eat_bonus.c \
					./srcs/philo_bonus/think_bonus.c \
					./srcs/philo_bonus/sleep_bonus.c \
					./srcs/philo/log.c

PHILO_OBJS = ${PHILO_SRCS:.c=.o}
PHILO_BONUS_OBJS = ${PHILO_SRCS_BONUS:.c=.o}

NAME = philo_one
BONUS_NAME = philo_bonus

SANITIZE = -g3 -fsanitize=address

all: $(NAME)

bonus: $(BONUS_NAME)

philo_one: $(PHILO_OBJS)
	gcc $(PHILO_OBJS) -o $(NAME)
	
philo_bonus: $(PHILO_BONUS_OBJS)
	gcc $(PHILO_BONUS_OBJS) -o $(BONUS_NAME) $(SANITIZE)

clean:
	rm -rf $(PHILO_OBJS)
	rm -rf $(PHILO_BONUS_OBJS)

fclean: clean
	rm -rf philo
	rm -rf philo_bonus

re: clean fclean
	all