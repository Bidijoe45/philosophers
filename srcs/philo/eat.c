#include <stdio.h>
#include "../philo.h"

void	philo_wait_for_forks(t_philo *philo, struct timeval absolute_time)
{
	struct timeval time;
	struct timeval waiting_time;

	//espera a que los dos tenedores esten libres
	gettimeofday(&time, NULL);
	gettimeofday(&waiting_time, NULL);
	while (philo->forks[philo->left_fork_id - 1].in_use || philo->forks[philo->right_fork_id - 1].in_use)
	{
		usleep(5000);
		if ((time.tv_sec - waiting_time.tv_sec) >= philo->time_to_die)
		{
			printf("|%5ld|-----Philo %d DIES 1----\n", time.tv_sec - absolute_time.tv_sec, philo->id);
			exit(1);
		}
		gettimeofday(&time, NULL);
	}	
}

void	philo_get_forks(t_philo *philo, struct timeval absolute_time)
{
	struct timeval time;

	//coge el tenedor izquierdo
	pthread_mutex_lock(&philo->forks[philo->left_fork_id - 1].mutex);
	philo->forks[philo->left_fork_id - 1].in_use = true;
	gettimeofday(&time, NULL);
	printf("|%5ld| Philo %d takes his left fork\n", time.tv_sec - absolute_time.tv_sec, philo->id);

	//coge el tenedor derecho
	pthread_mutex_lock(&philo->forks[philo->right_fork_id - 1].mutex);
	philo->forks[philo->right_fork_id - 1].in_use = true;
	gettimeofday(&time, NULL);
	printf("|%5ld| Philo %d takes his right fork\n", time.tv_sec - absolute_time.tv_sec, philo->id);
}

void	philo_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->forks[philo->left_fork_id - 1].mutex);
	philo->forks[philo->left_fork_id - 1].in_use = false;
	pthread_mutex_unlock(&philo->forks[philo->right_fork_id - 1].mutex);
	philo->forks[philo->right_fork_id - 1].in_use = false;
}


void	philo_eat(t_philo *philo, struct timeval absolute_time)
{
	struct timeval time;
	struct timeval eating_time;

	philo_wait_for_forks(philo, absolute_time);
	philo_get_forks(philo, absolute_time);

	//el filosofo comienza a comer
	printf("|%5ld| Philo %d started eating\n", time.tv_sec - absolute_time.tv_sec, philo->id);
	gettimeofday(&time, NULL);
	gettimeofday(&eating_time, NULL);
	while ((time.tv_sec - eating_time.tv_sec) <= philo->time_to_eat)
	{
		usleep(5000);
		if ((time.tv_sec - eating_time.tv_sec) >= philo->time_to_die)
		{
			printf("|%5ld|-----Philo %d DIES 2----\n", time.tv_sec - absolute_time.tv_sec, philo->id);
			exit(1);
			pthread_mutex_unlock(&philo->forks[philo->left_fork_id - 1].mutex);
			philo->forks[philo->left_fork_id - 1].in_use = false;
			pthread_mutex_unlock(&philo->forks[philo->right_fork_id - 1].mutex);
			philo->forks[philo->right_fork_id - 1].in_use = false;
		}
		gettimeofday(&time, NULL);
	}

	philo_release_forks(philo);

	printf("Philo %d ends eating\n", philo->id);
}