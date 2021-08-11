#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "philo_bonus.h"
#include "../aux/aux.h"
#include "../log/log_bonus.h"

void	philo_sleep(t_philo *philo)
{
	struct timeval	time;
	struct timeval	sleep_time;
	int				sleep_diff;

	gettimeofday(&time, NULL);
	sem_wait(philo->all_alive_mtx);
	philo_log(PHILO_SLEEP, philo, time, philo->ab_time);
	sem_post(philo->all_alive_mtx);
	ft_msleep(philo->time_to_sleep_ms);
	philo->state = THINKING;
}
