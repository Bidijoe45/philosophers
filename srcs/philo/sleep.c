#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "philo.h"
#include "../aux/aux.h"
#include "../log/log.h"

int	philo_sleep(t_philo *philo, struct timeval *ab_time)
{
	struct timeval	time;
	struct timeval	sleep_time;
	int				sleep_diff;

	gettimeofday(&time, NULL);
	pthread_mutex_lock(philo->all_alive_mtx);
	philo_log(PHILO_SLEEP, philo, time, *ab_time);
	pthread_mutex_unlock(philo->all_alive_mtx);
	gettimeofday(&sleep_time, NULL);
	sleep_diff = time_diff_us(time, sleep_time);
	while (sleep_diff <= philo->time_to_sleep_ms * 1000)
	{
		usleep(SLEEP_TIME);
		gettimeofday(&time, NULL);
		sleep_diff = time_diff_us(time, sleep_time);
	}
	return (0);
}
