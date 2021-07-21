#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "philo.h"
#include "../aux/aux.h"
#include "log.h"

void	philo_sleep(t_philo *philo, struct timeval *ab_time)
{
	struct timeval	time;
	struct timeval	sleep_time;
	int				sleep_diff;

	gettimeofday(&time, NULL);
	philo_log(PHILO_SLEEP, philo, time, *ab_time);
	
	gettimeofday(&sleep_time, NULL);
	sleep_diff = time_diff_us(time, sleep_time);
	while (sleep_diff <= philo->time_to_sleep_ms * 1000)
	{
		usleep(SLEEP_TIME);
		if (sleep_diff >= philo->time_to_die_ms * 1000)
		{
			pthread_mutex_lock(philo->all_alive_mtx);
			philo_log(PHILO_DEATH, philo, time, *ab_time);
			philo_set_all_alive(philo, false);
			pthread_mutex_unlock(philo->all_alive_mtx);
			exit(1);
		}
		gettimeofday(&time, NULL);
		sleep_diff = time_diff_us(time, sleep_time);
	}
}
