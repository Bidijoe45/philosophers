PHILO_SRCS =	./srcs/philo/philo.c \
				./srcs/philo/eat.c \
				./srcs/philo/think.c \
				./srcs/philo/sleep.c \
				./srcs/philo/thread.c \
				./srcs/philo/philo_init.c \
				./srcs/philo/monitor.c \
				./srcs/aux/ft_atoi.c \
				./srcs/aux/ft_isdigit.c \
				./srcs/aux/time_diff.c \
				./srcs/aux/ft_msleep.c \
				./srcs/parser/parser.c \
				./srcs/log/log.c

PHILO_SRCS_BONUS =	./srcs/philo_bonus/philo_bonus.c \
					./srcs/philo_bonus/eat_bonus.c \
					./srcs/philo_bonus/think_bonus.c \
					./srcs/philo_bonus/sleep_bonus.c \
					./srcs/philo_bonus/process_bonus.c \
					./srcs/philo_bonus/philo_init_bonus.c \
					./srcs/philo_bonus/monitor_bonus.c \
					./srcs/aux/ft_atoi.c \
					./srcs/aux/ft_isdigit.c \
					./srcs/aux/time_diff.c \
					./srcs/aux/ft_msleep.c \
					./srcs/parser/parser.c \
					./srcs/log/log_bonus.c

PHILO_OBJS = ${PHILO_SRCS:.c=.o}
PHILO_BONUS_OBJS = ${PHILO_SRCS_BONUS:.c=.o}

NAME = philo
BONUS_NAME = philo_bonus
CFLAGS= -Wall -Werror -Wextra
SANITIZE = -g3 -fsanitize=address

all: $(NAME)

bonus: $(BONUS_NAME)

philo: $(PHILO_OBJS)
	gcc $(PHILO_OBJS) -o $(NAME) $(SANITIZE) -pthread
	
philo_bonus: $(PHILO_BONUS_OBJS)
	gcc $(PHILO_BONUS_OBJS) -o $(BONUS_NAME) -pthread

clean:
	rm -rf $(PHILO_OBJS)
	rm -rf $(PHILO_BONUS_OBJS)

fclean: clean
	rm -rf philo
	rm -rf philo_bonus

re: fclean all

rebonus: fclean bonus