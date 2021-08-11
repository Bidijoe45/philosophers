#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include "philo_bonus.h"
#include "../aux/aux.h"
#include "../bool.h"
#include "../log/log_bonus.h"

void kill_philo(t_philo *philo, struct timeval time)
{
	sem_wait(philo->all_alive_mtx);
	philo_log(PHILO_DEATH, philo, time, philo->ab_time);
	*philo->all_alive = false;
	philo_release_forks(philo);
	sem_post(philo->all_alive_mtx);
	sem_close(philo->forks);
	sem_unlink(SEM_FORKS);
	sem_close(philo->all_alive_mtx);
	sem_unlink(SEM_ALL_ALIVE);
	exit(0);
}

void *check_philo_death_thread(void *philo_data)
{
	struct timeval	time;
	t_philo			*philo;

	philo = (t_philo *)philo_data;
	gettimeofday(&time, NULL);

	while (time_diff_ms(philo->eat_start, time) <= philo->time_to_die_ms)
	{
		gettimeofday(&time, NULL);
		usleep(CHECK_TIME);
	}

	kill_philo(philo, time);
	return (NULL);
}