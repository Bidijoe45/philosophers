#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include "philo.h"
#include "../parser/parser.h"
#include "../bool.h"
#include "../data.h"
#include "../log/log.h"

void clear_forks_mutexes(t_fork *forks, int n_philos)
{
	int i;

	i = 0;
	while (i < n_philos)
	{
		pthread_mutex_destroy(&forks[i].mutex);
		i++;
	}
}

void philo(t_data *data)
{
	t_fork *forks;
	t_philo *philos;
	t_bool all_alive;
	pthread_mutex_t all_alive_mtx;
	
	all_alive = true;
	forks = malloc(sizeof(t_fork) * data->n_philos);
	init_forks(forks, data->n_philos);
	philos = malloc(sizeof(t_philo) * data->n_philos);
	init_philos(philos, data, forks);
	pthread_mutex_init(&all_alive_mtx, NULL);
	init_all_alive(philos, data->n_philos, &all_alive, &all_alive_mtx);
	start_philos(philos, data->n_philos);
	join_philos(philos, data->n_philos);
	clear_forks_mutexes(forks, data->n_philos);
	pthread_mutex_destroy(&all_alive_mtx);
}

int main(int argc, char **argv)
{
	t_data *data;
	t_args_error args_err;

	data = malloc(sizeof(t_data));
	if (!data)
		exit(1);
	args_err = check_args(data, argc, argv);
	if (args_err)
	{
		if (args_err == N_OF_ARGS)
		printf("ERROR: Invalid number of arguments\n");
		else if (args_err == NEGATIVE_ARGS)
			printf("ERROR: Arguments cannot be negative\n");
		else if (args_err == NO_DIGIT)
			printf("ERROR: Arguments can be digits only\n");
		free(data);
		exit(1);
	}
	else
		philo(data);
	free(data);
	return (0);
}
