#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../philo.h"
#include "../aux/aux.h"
#include "../philo/log.h"

void	philo_sleep(t_philo *philo, struct timeval *ab_time)
{
	struct timeval	time;
	struct timeval	sleep_time;
	int				sleep_diff;

	gettimeofday(&time, NULL);
	philo_log(PHILO_SLEEP, philo->id, time, *ab_time);
	
	gettimeofday(&sleep_time, NULL);
	sleep_diff = time_diff_us(time, sleep_time);
	while (sleep_diff <= philo->time_to_sleep_ms)
	{
		usleep(5000);
		gettimeofday(&time, NULL);
		sleep_diff = time_diff_us(time, sleep_time);
	}
}
