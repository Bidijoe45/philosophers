#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include "philo.h"
#include "../parser/parser.h"
#include "../bool.h"
#include "../data.h"
#include "../log/log.h"

void philo(t_data *data)
{
	t_fork forks[data->n_philos];
	t_philo philos[data->n_philos];
	t_bool all_alive;
	pthread_mutex_t all_alive_mtx;

	all_alive = true;
	init_philos(philos, data, forks);
	pthread_mutex_init(&all_alive_mtx, NULL);
	init_all_alive(philos, data->n_philos, &all_alive, &all_alive_mtx);
	init_forks(forks, data->n_philos);
	start_philos(philos, data->n_philos);
	join_philos(philos, data->n_philos);
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
