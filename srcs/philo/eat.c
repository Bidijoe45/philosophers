#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../bool.h"
#include "philo.h"
#include "../aux/aux.h"
#include "../log/log.h"

static void	philo_get_forks(t_philo *philo, struct timeval *ab_time)
{
	struct timeval	time;

	philo->forks[philo->left_fork_id - 1].in_use = true;
	pthread_mutex_lock(&philo->forks[philo->left_fork_id - 1].mutex);
	gettimeofday(&time, NULL);
	pthread_mutex_lock(philo->all_alive_mtx);
	philo_log(PHILO_FORK, philo, time, *ab_time);
	pthread_mutex_unlock(philo->all_alive_mtx);
	philo->forks[philo->right_fork_id - 1].in_use = true;
	pthread_mutex_lock(&philo->forks[philo->right_fork_id - 1].mutex);
	gettimeofday(&time, NULL);
	pthread_mutex_lock(philo->all_alive_mtx);	
	philo_log(PHILO_FORK, philo, time, *ab_time);
	pthread_mutex_unlock(philo->all_alive_mtx);
}

void	philo_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->forks[philo->left_fork_id - 1].mutex);
	philo->forks[philo->left_fork_id - 1].in_use = false;
	pthread_mutex_unlock(&philo->forks[philo->right_fork_id - 1].mutex);
	philo->forks[philo->right_fork_id - 1].in_use = false;
}

static void	philo_wait_for_forks(t_philo *philo, struct timeval *ab_time)
{
	struct timeval	time;
	struct timeval	waiting_time;
	int				die_diff;

	gettimeofday(&time, NULL);
	gettimeofday(&waiting_time, NULL);
	while (philo->forks[philo->left_fork_id - 1].in_use
		|| philo->forks[philo->right_fork_id - 1].in_use)
	{
		usleep(SLEEP_TIME);
		die_diff = time_diff_us(time, waiting_time);
		if (die_diff >= (philo->time_to_die_ms * 1000))
		{
			philo_die_waiting(philo, time, *ab_time);
			printf("all_alive: %d\n", *philo->all_alive);
		}
		gettimeofday(&time, NULL);
	}
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
	pthread_mutex_lock(philo->all_alive_mtx);
	philo_log(PHILO_EAT, philo, time, *ab_time);
	pthread_mutex_unlock(philo->all_alive_mtx);
	gettimeofday(&eating_time, NULL);
	eat_diff = time_diff_us(time, eating_time);
	while (eat_diff <= (philo->time_to_eat_ms * 1000))
	{
		usleep(SLEEP_TIME);
		die_diff = time_diff_us(time, eating_time);
		if (die_diff >= (philo->time_to_die_ms * 1000))
		{
			philo_die_eating(philo, time, *ab_time);
		}
		gettimeofday(&time, NULL);
		eat_diff = time_diff_us(time, eating_time);
	}
	philo_release_forks(philo);
}
