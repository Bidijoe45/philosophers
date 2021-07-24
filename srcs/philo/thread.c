#include <pthread.h>
#include "philo.h"

void	start_philos(t_philo *philos, int n_philos)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		pthread_create(&(philos[i].thread), NULL, philo_thread, &(philos[i]));
		i++;
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
	struct timeval	ab_time;
	philo = (t_philo *)philo_data;
	gettimeofday(&ab_time, NULL);
	while (*philo->all_alive)
	{
		if (philo->state == EATING)
		{
			philo_eat(philo, &ab_time);
			philo->state = SLEEPING;
			philo->n_eat++;
			if (philo->n_eat == philo->ntimes_to_eat)
			{
				gettimeofday(&time, NULL);
				return (NULL);
			}
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