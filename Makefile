PHILO_SRCS = ./srcs/philo/philo.c ./srcs/aux/ft_atoi.c ./srcs/aux/ft_isdigit.c ./srcs/parser/parser.c ./srcs/philo/eat.c ./srcs/philo/think.c ./srcs/philo/sleep.c

PHILO_OBJS = ${PHILO_SRCS:.c=.o}
NAME = philo

all: $(NAME)

philo: $(PHILO_OBJS)
	gcc $(PHILO_OBJS) -o $(NAME)

clean:
	make clean -C ./lib/libft
	rm -rf $(PHILO_OBJS)

fclean: clean
	make fclean -C ./lib/libft
	rm -rf philo

re: clean fclean
	make re -C ./lib/libft
	all