#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "philo_bonus.h"

void	start_philos(t_philo *philos, int n_philos)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < n_philos)
	{
		pid = fork();
		if (pid)
			philo_process(&philos[i]);
		i += 2;
 	}
	usleep(1000);
	i = 1;
	while (i < n_philos)
	{
		pid = fork();
		if (pid)
			philo_process(&philos[i]);
		i += 2;
 	}
}
	
void	wait_philos(t_philo *philos, int n_philos)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		wait(NULL);
		i++;
	}
}

void	philo_process(t_philo *philo)
{
	struct timeval	time;
	int				dead;

	philo->state = EATING;
	while (*philo->all_alive)
	{
		if (philo->state == EATING)
		{
			philo_eat(philo);
			philo->n_eat++;
			if (philo->n_eat == philo->ntimes_to_eat)
			{
				philo->state = DONE;
				break ;
				//TODO: implementar veces que han comido
			}
		}
		else if (philo->state == SLEEPING)
			philo_sleep(philo);
		else if (philo->state == THINKING)
			philo_think(philo);
	}
}
