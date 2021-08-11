#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "philo_bonus.h"
#include "../aux/aux.h"

void	start_philos(t_philo *philos, int n_philos)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < n_philos)
	{
		pid = fork();
		philos[i].pid = pid;
		if (pid)
			philo_process(&philos[i]);
		i += 2;
 	}
	usleep(1000);
	i = 1;
	while (i < n_philos)
	{
		pid = fork();
		philos[i].pid = pid;
		if (pid)
			philo_process(&philos[i]);
		i += 2;
 	}
}
	
void	wait_philos(t_philo *philos, int n_philos)
{
	int	i;
	int status;

	i = 0;
	while (i < n_philos)
	{
		waitpid(philos[i].pid, &status, 0);
		i++;
	}
}

void	philo_process(t_philo *philo)
{
	struct timeval	time;
	int				dead;
	pthread_t		death_check_thread;

	philo->state = EATING;
	pthread_create(&death_check_thread, NULL, &check_philo_death_thread, philo);
	while (*philo->all_alive)
	{
		if (philo->state == EATING)
		{
			philo_eat(philo);
			philo->n_eat++;
			if (philo->n_eat == philo->ntimes_to_eat)
			{
				philo->state = DONE;
				exit(0);
			}
		}
		else if (philo->state == SLEEPING)
			philo_sleep(philo);
		else if (philo->state == THINKING)
			philo_think(philo);
	}
}
