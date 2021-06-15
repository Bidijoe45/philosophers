#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


#include "../philo.h"
#include "../parser/parser.h"

void philo_one(t_philo *philo)
{

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
	e_parser_error	parser_err;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		exit(1);
	
	parser_err = parse_args(philo, argc, argv);
	if (parser_err == n_of_args)
		printf("Invalid number of arguments\n");
	else if (parser_err == negative_args)
		printf("Arguments cannot be negative\n");
    else if (parser_err == only_digits)
        printf("Arguments can only be digits\n");
	else
		philo_one(philo);

    printf("n_philos: %d\n", philo->n_philos);
    printf("time_to_die: %d\n", philo->time_to_die);
    printf("time_to_eat: %d\n", philo->time_to_eat);
    printf("time_to_sleep: %d\n", philo->time_to_sleep);
    printf("n_eat: %d\n", philo->n_eat);


	free(philo);
	return (0);
}

