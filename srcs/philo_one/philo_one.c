#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <pthread.h>

#include "../philo.h"
#include "../parser/parser.h"
#include "../../lib/libft/libft.h"

void init_data(t_data *data)
{
    data->n_philos = -1;
    data->time_to_die = -1;
    data->time_to_eat = -1;
    data->time_to_sleep = -1;
    data->n_eat = -1;
}

void init_philos(t_philo *philos, int n_philos)
{
	int i;

	i = 0;
	while (i < n_philos)
	{
		philos[i].id = i + 1;
		philos[i].state = EATING;
		i++;
	}
}

void *philo(t_philo *philo)
{
	

	return (NULL);
}

void start_philos(t_philo *philos, int n_philos)
{
	int i;
	pthread_t philos_t[n_philos];

	i = 0;
	while (i < n_philos)
	{
		pthread_create(&philos_t[i], NULL, &philo, &(philos[i]));
		i++;
	}
}

void philo_one(t_data *data)
{
	t_fork forks[data->n_philos];
	t_philo philos[data->n_philos];

	init_philos(philos, data->n_philos);
	start_philos(philos, data->n_philos);
}

int main(int argc, char **argv)
{
	t_data			*data;
	t_args_error	args_err;

	data = malloc(sizeof(t_data));
	if (!data)
		exit(1);
	init_data(data);

	args_err = check_args(data, argc, argv);
	if (args_err == N_OF_ARGS)
		printf("ERROR: Invalid number of arguments\n");
	else if (args_err == NEGATIVE_ARGS)
		printf("ERROR: Arguments cannot be negative\n");
	else if (args_err == NO_DIGIT)
		printf("ERROR: Arguments can be digits only\n");
	else
		philo_one(data);

	free(data);
	
	return (0);
}

