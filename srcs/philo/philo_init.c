#include "philo.h"

void	init_forks(t_fork *forks, int n_philos)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		forks[i].in_use = false;
		pthread_mutex_init(&forks[i].mutex, NULL);
		i++;
	}
}

void	init_philos(t_philo *philos, t_data *data, t_fork *forks)
{
	int	i;
	int	id;

	i = 0;
	while (i < data->n_philos)
	{
		philos[i].id = (i + 1);
		philos[i].state = EATING;
		philos[i].forks = forks;
		philos[i].left_fork_id = (i + 1);
		if ((i + 1) == 1)
			philos[i].right_fork_id = data->n_philos;
		else
			philos[i].right_fork_id = i;
		philos[i].time_to_die_ms = data->time_to_die;
		philos[i].time_to_eat_ms = data->time_to_eat;
		philos[i].time_to_sleep_ms = data->time_to_sleep;
		philos[i].ntimes_to_eat = data->ntimes_to_eat;
		philos[i].n_eat = 0;
		i++;
	}
}


void init_all_alive(t_philo *philos, int n_philos, t_bool *all_alive,
                        pthread_mutex_t *all_alive_mtx)
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