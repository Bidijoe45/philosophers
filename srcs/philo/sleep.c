#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../philo.h"

void philo_sleep(t_philo *philo, struct timeval *absolute_time)
{
	struct timeval time;
	struct timeval sleep_time;
	int sleep_diff;

	printf("|%5ld| Philo %d started sleeping\n", time.tv_sec - absolute_time->tv_sec, philo->id);
	//el filosofo comienza a dormir
	gettimeofday(&time, NULL);
	gettimeofday(&sleep_time, NULL);
	sleep_diff = ((time.tv_sec - sleep_time.tv_sec) * 1000000) + (time.tv_usec - sleep_time.tv_usec);
	while (sleep_diff <= philo->time_to_sleep_ms)
	{
		usleep(5000);
		gettimeofday(&time, NULL);
		sleep_diff = ((time.tv_sec - sleep_time.tv_sec) * 1000000) + (time.tv_usec - sleep_time.tv_usec);
	}

	printf("|%5ld| Philo %d ends sleeping\n", time.tv_sec - absolute_time->tv_sec, philo->id);
}