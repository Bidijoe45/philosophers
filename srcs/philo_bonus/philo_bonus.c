#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include "philo_bonus.h"
#include "../parser/parser.h"
#include "../bool.h"
#include "../data.h"
#include "../log/log_bonus.h"
#include "../aux/aux.h"

#include <errno.h>
#include <string.h>

void philo_bonus(t_data *data)
{
	t_fork			*forks;
	t_philo			*philos;
	t_bool			all_alive;
	sem_t			*all_alive_mtx;
	struct timeval	ab_time;
	
	//FIXME:	de verdad hace falta limpiar los semaforos al principio
	//			o e solo una ilusion?
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_ALL_ALIVE);

	forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 0644, data->n_philos);
	if (forks == SEM_FAILED)
		printf("Cannot create forks semaphore: %s\n", strerror(errno));

	philos = malloc(sizeof(t_philo) * data->n_philos);
	init_philos(philos, data, forks);

	all_alive_mtx = sem_open(SEM_ALL_ALIVE, O_CREAT | O_EXCL, 0644, 1);
	if (all_alive_mtx == SEM_FAILED)
		printf("Cannot create all_alive_mtx semaphore: %s\n", strerror(errno));

	all_alive = true;
	init_all_alive(philos, data->n_philos, &all_alive, all_alive_mtx);
	gettimeofday(&ab_time, NULL);
	init_philos_time(philos, data->n_philos, &ab_time);
	start_philos(philos, data->n_philos);
	wait_philos(philos, data->n_philos);

	sem_close(forks);
	sem_unlink(SEM_FORKS);
	sem_close(all_alive_mtx);
	sem_unlink(SEM_ALL_ALIVE);

	free(philos);
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
		philo_bonus(data);
	free(data);
	return (0);
}
