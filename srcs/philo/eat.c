#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../bool.h"
#include "../philo.h"

void	philo_wait_for_forks(t_philo *philo, struct timeval *absolute_time)
{
	struct timeval time;
	struct timeval waiting_time;
	int die_diff;

	//espera a que los dos tenedores esten libres
	gettimeofday(&time, NULL);
	gettimeofday(&waiting_time, NULL);
	while (philo->forks[philo->left_fork_id - 1].in_use || philo->forks[philo->right_fork_id - 1].in_use)
	{
		usleep(5000);
		die_diff = ((time.tv_sec - waiting_time.tv_sec) * 1000000) + (time.tv_usec - waiting_time.tv_usec);
		if (die_diff >= philo->time_to_die_ms * 1000)
		{
			printf("|%5ld|+Philo %d DIES+\n", time.tv_sec - absolute_time->tv_sec, philo->id);
			*philo->all_alive = false;
			exit(1);
		}
		gettimeofday(&time, NULL);
		die_diff = ((time.tv_sec - waiting_time.tv_sec) * 1000000) + (time.tv_usec - waiting_time.tv_usec);
	}
}

void	philo_get_forks(t_philo *philo, struct timeval *absolute_time)
{
	struct timeval time;

	//coge el tenedor izquierdo
	pthread_mutex_lock(&philo->forks[philo->left_fork_id - 1].mutex);
	philo->forks[philo->left_fork_id - 1].in_use = true;
	gettimeofday(&time, NULL);
	printf("|%5ld| Philo %d takes his left fork\n", time.tv_sec - absolute_time->tv_sec, philo->id);

	//coge el tenedor derecho
	pthread_mutex_lock(&philo->forks[philo->right_fork_id - 1].mutex);
	philo->forks[philo->right_fork_id - 1].in_use = true;
	gettimeofday(&time, NULL);
	printf("|%5ld| Philo %d takes his right fork\n", time.tv_sec - absolute_time->tv_sec, philo->id);
}

void	philo_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->forks[philo->left_fork_id - 1].mutex);
	philo->forks[philo->left_fork_id - 1].in_use = false;
	pthread_mutex_unlock(&philo->forks[philo->right_fork_id - 1].mutex);
	philo->forks[philo->right_fork_id - 1].in_use = false;
}


void	philo_eat(t_philo *philo, struct timeval *absolute_time)
{
	struct timeval time;
	struct timeval eating_time;
	int die_diff;
	int eat_diff;

	philo_wait_for_forks(philo, absolute_time);
	philo_get_forks(philo, absolute_time);

	//el filosofo comienza a comer
	gettimeofday(&time, NULL);
	printf("|%5ld| Philo %d started eating\n", time.tv_sec - absolute_time->tv_sec, philo->id);
	gettimeofday(&eating_time, NULL);
	eat_diff = ((time.tv_sec - eating_time.tv_sec) * 1000000) + (time.tv_usec - eating_time.tv_usec);
	while (eat_diff <= philo->time_to_eat_ms * 1000)
	{
		usleep(5000);
		die_diff = ((time.tv_sec - eating_time.tv_sec) * 1000000) + (time.tv_usec - eating_time.tv_usec);
		if (die_diff >= philo->time_to_die_ms * 1000)
		{
			printf("|%5ld|+Philo %d DIES+\n", time.tv_sec - absolute_time->tv_sec, philo->id);
			*philo->all_alive = false;
			pthread_mutex_unlock(&philo->forks[philo->left_fork_id - 1].mutex);
			philo->forks[philo->left_fork_id - 1].in_use = false;
			pthread_mutex_unlock(&philo->forks[philo->right_fork_id - 1].mutex);
			philo->forks[philo->right_fork_id - 1].in_use = false;
			exit(1);
		}
		gettimeofday(&time, NULL);
		eat_diff = ((time.tv_sec - eating_time.tv_sec) * 1000000) + (time.tv_usec - eating_time.tv_usec);
	}

	philo_release_forks(philo);

	printf("|%5ld| Philo %d ends eating\n", time.tv_sec - absolute_time->tv_sec, philo->id);
}