#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

#include "philo_bonus.h"
#include "../parser/parser.h"
#include "../bool.h"

void	init_data(t_data *data)
{
	data->n_philos = -1;
	data->time_to_die = -1;
	data->time_to_eat = -1;
	data->time_to_sleep = -1;
	data->ntimes_to_eat = -1;
}

void	init_philos(t_philo *philos, t_data *data, t_bool *all_alive, t_forks *forks)
{
	int	i;
	int	id;

	i = 0;
	while (i < data->n_philos)
	{
		philos[i].id = (i + 1);
		philos[i].state = EATING;
		philos[i].all_alive = all_alive;
		philos[i].forks = forks;
		philos[i].time_to_die_ms = data->time_to_die;
		philos[i].time_to_eat_ms = data->time_to_eat;
		philos[i].time_to_sleep_ms = data->time_to_sleep;
		philos[i].ntimes_to_eat = data->ntimes_to_eat;
		philos[i].n_eat = 0;
		i++;
	}
}

void	*philo_process(t_philo *philo)
{
	struct timeval	time;
	struct timeval	ab_time;

	while (*philo->all_alive)
	{
		if (philo->state == EATING)
		{
			philo_eat(philo, &ab_time);
			philo->n_eat++;
			if (philo->n_eat == philo->ntimes_to_eat)
			{
				gettimeofday(&time, NULL);
				return (NULL);
			}
			philo->state = SLEEPING;
		}
		else if (philo->state == SLEEPING)
		{
			philo_sleep(philo, &ab_time);
			philo->state = THINKING;
		}
		else if (philo->state == THINKING)
		{
			philo_think(philo, &ab_time);
			philo->state = EATING;
		}
	}

	return (NULL);
}

void	start_philos(t_philo *philos, int n_philos)
{
	int	i;
	pid_t pid;

	i = 0;
	while (i < n_philos)
	{
		pid = fork();
		if (pid == 0)
		{
			philo_process(&philos[i]);
			exit(1);
		}
		i++;
	}
}

void	init_forks(t_forks *forks, int n_philos)
{
	forks->n_forks = n_philos;
	forks->sem_forks = sem_open("sem_forks", O_CREAT);
}

void	philo_bonus(t_data *data)
{
	t_philo	philos[data->n_philos];
	t_bool	all_alive;
	t_forks forks;

	all_alive = true;
	init_philos(philos, data, &all_alive, &forks);
	init_forks(&forks, data->n_philos);
	start_philos(philos, data->n_philos);
}

int	main(int argc, char **argv)
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
		philo_bonus(data);
	free(data);
	return (0);
}