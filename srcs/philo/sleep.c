#include <stdio.h>
#include "../philo.h"

void philo_sleep(t_philo *philo, struct timeval absolute_time)
{
	struct timeval time;
	struct timeval sleep_time;

	printf("Philo %d started sleeping\n", philo->id);
	//el filosofo comienza a dormir
	gettimeofday(&time, NULL);
	gettimeofday(&sleep_time, NULL);
	while ((time.tv_sec - sleep_time.tv_sec) <= philo->time_to_sleep)
	{
		usleep(5000);
		gettimeofday(&time, NULL);
	}

	printf("Philo %d ends sleeping\n", philo->id);
}