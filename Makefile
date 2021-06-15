PHILO_ONE_SRCS = ./srcs/philo_one/philo_one.c ./srcs/parser/parser.c
PHILO_TWO_SRCS = 
PHILO_THREE_SRCS = 

PHILO_ONE_OBJS = ${PHILO_ONE_SRCS:.c=.o}
PHILO_TWO_OBJS = ${PHILO_TWO_SRCS:.c=.o}
PHILO_THREE_OBJS = ${PHILO_THREE_SRCS:.c=.o}

all: philo_one philo_two philo_three

philo_one: $(PHILO_ONE_OBJS)
	gcc $(PHILO_ONE_OBJS) -o philo_one

philo_two: $(PHILO_TWO_OBJS)
	gcc $(PHILO_TWO_OBJS) -o philo_two

philo_three: $(PHILO_THREE_OBJS)
	gcc $(PHILO_THREE_OBJS) -o philo_three

clean:
	rm -rf $(PHILO_ONE_OBJS) $(PHILO_TWO_OBJS) $(PHILO_THREE_OBJS)

fclean: clean
	rm -rf philo_one philo_two philo_three