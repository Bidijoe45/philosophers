#include <semaphore.h>
#include "philo_bonus.h"


void	init_philos(t_philo *philos, t_data *data, t_fork *forks)
{
	int	i;
	int	id;

	i = 0;
	while (i < data->n_philos)
	{
		philos[i].id = (i + 1);
		philos[i].state = UNINITIALIZED;
		philos[i].forks = forks;
		philos[i].time_to_die_ms = data->time_to_die;
		philos[i].time_to_eat_ms = data->time_to_eat;
		philos[i].time_to_sleep_ms = data->time_to_sleep;
		philos[i].ntimes_to_eat = data->ntimes_to_eat;
		philos[i].n_eat = 0;
		i++;
	}
}

void init_all_alive(t_philo *philos, int n_philos, t_bool *all_alive,
                        sem_t *all_alive_mtx)
{
	int i;

	i = 0;
	while (i < n_philos)
	{
		philos[i].all_alive = all_alive;
		philos[i].all_alive_mtx = all_alive_mtx;
		i++;
	}
}

void init_philos_time(t_philo *philos, int n_philos, struct timeval *ab_time)
{
	int i;

	i = 0;
	while (i < n_philos)
	{
		philos[i].ab_time = *ab_time;
		gettimeofday(&philos[i].eat_start, NULL);
		i++;
	}
}