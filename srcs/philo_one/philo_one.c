#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#include "../philo.h"
#include "../parser/parser.h"
#include "../../lib/libft/libft.h"

void init_data(t_data *data)
{
    data->n_philos = -1;
    data->time_to_die = -1;
    data->time_to_eat = -1;
    data->time_to_sleep = -1;
    data->n_eat = -1;
}

void init_forks(t_fork *forks, int n_philos)
{
	int i;

	i = 0;
	while (i < n_philos)
	{
		forks[i].in_use = false;
		pthread_mutex_init(&forks[i].mutex, NULL);
		i++;
	}
}

void init_philos(t_philo *philos, t_data *data, t_bool *all_alive, t_fork *forks)
{
	int i;
	int id;

	i = 0;
	while (i <= data->n_philos)
	{
		philos[i].id = (i + 1);
		philos[i].state = EATING;
		philos[i].all_alive = all_alive;
		philos[i].forks = forks;
		philos[i].left_fork_id = (i + 1);
		if ((i + 1) == 1)
			philos[i].right_fork_id = data->n_philos;
		else
			philos[i].right_fork_id = i;
		philos[i].time_to_die = data->time_to_die;
		philos[i].time_to_eat = data->time_to_eat;
		philos[i].time_to_sleep = data->time_to_sleep;
		i++;
	}
}

void *philo(void *philo_data)
{
	t_philo *philo;
	struct timeval time;
	long int start_time;
	long int reset_time;
	long int old_time;
	int i_s;
	int i_ms;

	philo = (t_philo *)philo_data;

	printf("Philo %d starts\n", philo->id);

	gettimeofday(&time, NULL);
	start_time = time.tv_sec;
	reset_time = 0;

	while (philo->all_alive)
	{
		if (philo->state == EATING)
		{
			//espera a que los dos tenedores esten libres
			gettimeofday(&time, NULL);
			old_time = time.tv_sec;
			while (philo->forks[philo->left_fork_id - 1].in_use || philo->forks[philo->right_fork_id - 1].in_use)
			{
				usleep(5000);
				gettimeofday(&time, NULL);
				if ((time.tv_sec - old_time) >= philo->time_to_die)
				{
					printf("-----------------------Philo %d DIES 1-----------------------\n", philo->id);
				}
				old_time = time.tv_sec;
			}
			
			//coge el tenedor izquierdo
			pthread_mutex_lock(&philo->forks[philo->left_fork_id - 1].mutex);
			philo->forks[philo->left_fork_id - 1].in_use = true;
			gettimeofday(&time, NULL);
			printf("|%5ld| Philo %d takes his left fork\n", time.tv_sec - start_time, philo->id);

			//coge el tenedor derecho
			pthread_mutex_lock(&philo->forks[philo->right_fork_id - 1].mutex);
			philo->forks[philo->right_fork_id - 1].in_use = true;
			gettimeofday(&time, NULL);
			printf("|%5ld| Philo %d takes his right fork\n", time.tv_sec - start_time, philo->id);

			//el filosofo comienza a comer
			printf("|%5ld| Philo %d started eating\n", time.tv_sec - start_time, philo->id);
			gettimeofday(&time, NULL);
			old_time = time.tv_usec;
			while ((time.tv_sec - old_time) >= philo->time_to_eat)
			{
				usleep(5000);
				printf("resta: %ld\n", time.tv_sec - old_time);
				if ((time.tv_sec - old_time) >= philo->time_to_die)
				{
					printf("-----------------------Philo %d DIES 2-----------------------\n", philo->id);
					*philo->all_alive = false;
					exit(1);
				}
				gettimeofday(&time, NULL);
			}
			
			pthread_mutex_unlock(&philo->forks[philo->left_fork_id - 1].mutex);
			philo->forks[philo->left_fork_id - 1].in_use = false;
			pthread_mutex_unlock(&philo->forks[philo->right_fork_id - 1].mutex);
			philo->forks[philo->right_fork_id - 1].in_use = false;

			printf("Philo %d ends eating\n", philo->id);
			philo->state = SLEEPING;
		}
		else if (philo->state == SLEEPING)
		{
			printf("Philo %d started sleeping\n", philo->id);
			//el filosofo comienza a dormir
			i_ms = 0;
			while (i_ms < philo->time_to_eat * 1000)
			{
				usleep(5000);

				i_ms += 5;
			}

			philo->state = THINKING;
			printf("Philo %d ends sleeping\n", philo->id);
		}
		else if (philo->state == THINKING)
		{
			printf("Philo %d thinks\n", philo->id);
			philo->state = EATING;
		}

	}

	printf("Philo %d ends\n", philo->id);

	return (&philo->id);
}

void start_philos(t_philo *philos, int n_philos)
{
	int i;

	i = 0;
	while (i < n_philos)
	{
		pthread_create(&(philos[i].thread), NULL, philo, &(philos[i]));
		i++;
	}
}

void join_philos(t_philo *philos, int n_philos)
{
	int  i;

	i = 0;
	while (i < n_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

void philo_one(t_data *data)
{
	t_fork forks[data->n_philos];
	t_philo philos[data->n_philos];
	t_bool all_alive;

	all_alive = true;
	init_philos(philos, data, &all_alive, forks);	
	init_forks(forks, data->n_philos);
	start_philos(philos, data->n_philos);
	join_philos(philos, data->n_philos);
}

int main(int argc, char **argv)
{
	t_data			*data;
	t_args_error	args_err;

	data = malloc(sizeof(t_data));
	if (!data)
		exit(1);
	init_data(data);

	args_err = check_args(data, argc, argv);
	if (args_err == N_OF_ARGS)
		printf("ERROR: Invalid number of arguments\n");
	else if (args_err == NEGATIVE_ARGS)
		printf("ERROR: Arguments cannot be negative\n");
	else if (args_err == NO_DIGIT)
		printf("ERROR: Arguments can be digits only\n");
	else
		philo_one(data);

	free(data);
	
	return (0);
}

