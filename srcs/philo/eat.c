#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../bool.h"
#include "philo.h"
#include "../aux/aux.h"
#include "log.h"

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

	pthread_mutex_lock(&philo->forks[philo->left_fork_id - 1].mutex);
	philo->forks[philo->left_fork_id - 1].in_use = true;
	gettimeofday(&time, NULL);
	pthread_mutex_lock(&philo->forks[philo->right_fork_id - 1].mutex);
	philo->forks[philo->right_fork_id - 1].in_use = true;
	gettimeofday(&time, NULL);
}

static void	philo_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->forks[philo->left_fork_id - 1].mutex);
	philo->forks[philo->left_fork_id - 1].in_use = false;
	pthread_mutex_unlock(&philo->forks[philo->right_fork_id - 1].mutex);
	philo->forks[philo->right_fork_id - 1].in_use = false;
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
			pthread_mutex_unlock(&philo->forks[philo->left_fork_id - 1].mutex);
			philo->forks[philo->left_fork_id - 1].in_use = false;
			pthread_mutex_unlock(&philo->forks[philo->right_fork_id - 1].mutex);
			philo->forks[philo->right_fork_id - 1].in_use = false;
			exit(1);
		}
		gettimeofday(&time, NULL);
		eat_diff = time_diff_us(time, eating_time);
	}
	philo_release_forks(philo);
}
