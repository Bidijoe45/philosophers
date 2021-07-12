#include <stdio.h>
#include <sys/time.h>
#include "../philo.h"
#include "log.h"

void	philo_think(t_philo *philo, struct timeval *ab_time)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	philo_log(PHILO_THINK, philo->id, time, *ab_time);
}
