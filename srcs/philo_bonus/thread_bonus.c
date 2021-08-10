#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "philo.h"

void	start_philos(t_philo *philos, int n_philos)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		pthread_create(&(philos[i].thread), NULL, philo_thread, &(philos[i]));
		i += 2;
 	}
	usleep(1000);
	i = 1;
	while (i < n_philos)
	{
		pthread_create(&(philos[i].thread), NULL, philo_thread, &(philos[i]));
		i += 2;
 	}
}
	
void	join_philos(t_philo *philos, int n_philos)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

void	*philo_thread(void *philo_data)
{
	t_philo			*philo;
	struct timeval	time;
	int				dead;

	philo = (t_philo *)philo_data;
	philo->state = EATING;
	while (*philo->all_alive)
	{
		if (philo->state == EATING)
		{
			dead = philo_eat(philo);
			if (dead)
				break ;
			philo->state = SLEEPING;
			philo->n_eat++;
			if (philo->n_eat == philo->ntimes_to_eat)
			{
				philo->state = DONE;
				break ;
			}
		}
		else if (philo->state == SLEEPING)
		{
			dead = philo_sleep(philo);
			if (dead)
				break ;
			philo->state = THINKING;
		}
		else if (philo->state == THINKING)
		{
			philo_think(philo);
			philo->state = EATING;
		}
	}
	return (NULL);
}
