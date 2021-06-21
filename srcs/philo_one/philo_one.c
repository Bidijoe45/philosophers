#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


#include "../philo.h"
#include "../parser/parser.h"
#include "../../lib/libft/libft.h"

void philo_one(t_philo *philo)
{
	printf("Philo one\n");
}

void init_philo(t_philo *philo)
{
    philo->n_philos = -1;
    philo->time_to_die = -1;
    philo->time_to_eat = -1;
    philo->time_to_sleep = -1;
    philo->n_eat = -1;
}

int main(int argc, char **argv)
{
	t_philo *philo;
	t_parser_error	parser_err;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		exit(1);
	
	parser_err = parse_args(argc, argv);
	if (parser_err == N_OF_ARGS)
		printf("Invalid number of arguments\n");
	else if (parser_err == NEGATIVE_ARGS)
		printf("Arguments cannot be negative\n");
	else if (parser_err == NO_DIGIT)
		printf("Arguments can be digits only\n");
	else
		philo_one(philo);

	free(philo);
	
	return (0);
}

