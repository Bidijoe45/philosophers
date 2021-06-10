PHILO_ONE_SRCS = ./srcs/philo_one.c
PHILO_TWO_SRCS = ./srcs/philo_one.c
PHILO_THREE_SRCS = ./srcs/philo_one.c

PHILO_ONE_OBJS = ${PHILO_ONE_SRCS:.c=.o}
PHILO_TWO_OBJS = ${PHILO_TWO_OBJS:.c=.o}
PHILO_THREE_OBJS = ${PHILO_THREE_OBJS:.c=.o}

philo_one: $(PHILO_ONE_OBJS)
