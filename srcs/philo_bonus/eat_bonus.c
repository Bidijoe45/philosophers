#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include "../bool.h"
#include "philo_bonus.h"
#include "../aux/aux.h"
#include "../philo/log.h"

static void	philo_wait_for_forks(t_philo *philo, struct timeval *ab_time)
{
	struct timeval	time;
	struct timeval	waiting_time;
	int				die_diff;

	gettimeofday(&time, NULL);
	gettimeofday(&waiting_time, NULL);
	while (philo->forks->n_forks <= 0)
	{
		usleep(5000);
		die_diff = time_diff_us(time, waiting_time);
		if (die_diff >= philo->time_to_die_ms * 1000)
		{
			philo_log(PHILO_DEATH, philo->id, time, *ab_time);
			*philo->all_alive = false;
			exit(1);
		}
		gettimeofday(&time, NULL);
		die_diff = time_diff_us(time, waiting_time);
	}
}

static void	philo_get_forks(t_philo *philo, struct timeval *ab_time)
{
	struct timeval	time;

	sem_wait(philo->forks->sem_forks);
	philo->forks->n_forks--;
	gettimeofday(&time, NULL);

	sem_wait(philo->forks->sem_forks);
	philo->forks->n_forks--;
	gettimeofday(&time, NULL);
}

static void	philo_release_forks(t_philo *philo)
{
	sem_post(philo->forks->sem_forks);
	philo->forks->n_forks++;
	sem_post(philo->forks->sem_forks);
	philo->forks->n_forks++;
}

void	philo_eat(t_philo *philo, struct timeval *ab_time)
{
	struct timeval	time;
	struct timeval	eating_time;
	int				die_diff;
	int				eat_diff;

	philo_wait_for_forks(philo, ab_time);
	philo_get_forks(philo, ab_time);
	gettimeofday(&time, NULL);
	philo_log(PHILO_EAT, philo->id, time, *ab_time);
	gettimeofday(&eating_time, NULL);
	eat_diff = time_diff_us(time, eating_time);
	while (eat_diff <= philo->time_to_eat_ms * 1000)
	{
		usleep(5000);
		die_diff = time_diff_us(time, eating_time);
		if (die_diff >= philo->time_to_die_ms * 1000)
		{
			philo_log(PHILO_DEATH, philo->id, time, *ab_time);
			*philo->all_alive = false;
			sem_post(philo->forks->sem_forks);
			philo->forks->n_forks++;
			sem_post(philo->forks->sem_forks);
			philo->forks->n_forks++;
			exit(1);
		}
		gettimeofday(&time, NULL);
		eat_diff = time_diff_us(time, eating_time);
	}
	philo_release_forks(philo);
}
