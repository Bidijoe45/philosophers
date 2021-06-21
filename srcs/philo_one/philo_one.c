#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>

#include "../philo.h"
#include "../parser/parser.h"
#include "../../libft/libft.h"

void philo_one(t_philo *philo)
{
	printf("Philo one\n");
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

