#include <stdio.h>
#include <sys/time.h>
#include "philo.h"
#include "../log/log.h"

void	philo_think(t_philo *philo, struct timeval *ab_time)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	pthread_mutex_lock(philo->all_alive_mtx);
	philo_log(PHILO_THINK, philo, time, *ab_time);
	pthread_mutex_unlock(philo->all_alive_mtx);
}
