PHILO_ONE_SRCS = ./srcs/philo_one/philo_one.c ./srcs/parser/parser.c ./srcs/philo_one/eat.c
PHILO_TWO_SRCS = 
PHILO_THREE_SRCS = 

PHILO_ONE_OBJS = ${PHILO_ONE_SRCS:.c=.o}
PHILO_TWO_OBJS = ${PHILO_TWO_SRCS:.c=.o}
PHILO_THREE_OBJS = ${PHILO_THREE_SRCS:.c=.o}

LIBFT=./lib/libft

all: philo_one

libft:
	make -C $(LIBFT)

philo_one: libft $(PHILO_ONE_OBJS)
	gcc $(PHILO_ONE_OBJS) -o philo_one -L$(LIBFT) -lft

philo_two: $(PHILO_TWO_OBJS)
	gcc $(PHILO_TWO_OBJS) -o philo_two

philo_three: $(PHILO_THREE_OBJS)
	gcc $(PHILO_THREE_OBJS) -o philo_three

clean:
	make clean -C ./lib/libft
	rm -rf $(PHILO_ONE_OBJS) $(PHILO_TWO_OBJS) $(PHILO_THREE_OBJS)

fclean: clean
	make fclean -C ./lib/libft
	rm -rf philo_one philo_two philo_three

re: clean fclean
	make re -C ./lib/libft
	all