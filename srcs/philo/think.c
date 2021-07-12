#include <stdio.h>
#include <sys/time.h>
#include "../philo.h"

void philo_think(t_philo *philo, struct timeval *absolute_time)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	printf("|%5ld| Philo %d thinks\n", time.tv_sec - absolute_time->tv_sec, philo->id);
}