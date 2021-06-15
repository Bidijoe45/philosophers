#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>

#include "../philo.h"
#include "../parser/parser.h"

void philo_one(t_philo *philo)
{

}

int main(int argc, char **argv)
{
	t_philo *philo;
	e_parser_error	parser_err;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		exit(1);
	
	parser_err = parse_args(argc, argv);
	if (parser_err == n_of_args)
		printf("Invalid number of arguments\n");
	else if (parser_err == negative_args)
		printf("Arguments cannot be negative\n");
	else
		philo_one(philo);


	free(philo);
	return (0);
}

