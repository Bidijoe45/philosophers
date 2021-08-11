#include <stdio.h>
#include <sys/time.h>
#include "philo_bonus.h"
#include "../log/log_bonus.h"

void	philo_think(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	sem_wait(philo->all_alive_mtx);
	philo_log(PHILO_THINK, philo, time, philo->ab_time);
	sem_post(philo->all_alive_mtx);
	philo->state = EATING;
}
