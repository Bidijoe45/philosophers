/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 19:59:01 by apavel            #+#    #+#             */
/*   Updated: 2021/09/13 12:00:58 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include "philo_bonus.h"
#include "parser/parser.h"
#include "bool.h"
#include "data.h"
#include "log/log_bonus.h"
#include "aux/aux.h"

void	close_semaphores(t_fork *forks, sem_t *all_alive_mtx)
{
	sem_close(forks);
	sem_unlink(SEM_FORKS);
	sem_close(all_alive_mtx);
	sem_unlink(SEM_ALL_ALIVE);
}

void	finish_philo(t_philo *philos, int n_philos, int status, t_bool *died)
{
	int				i;
	struct timeval	time;

	i = 0;
	while (i < n_philos)
	{
		if (philos[i].id == status)
		{
			gettimeofday(&time, NULL);
			if (!*died)
				philo_log(PHILO_DEATH, &philos[i], time, philos[i].ab_time);
			*died = true;
			break ;
		}
		i++;
	}
	sigkill_all_philos(philos, n_philos);
}

void	wait_philos(t_philo *philos, int n_philos)
{
	int				status;
	int				done;
	int				i;
	t_bool			died;

	status = 0;
	done = 0;
	died = false;
	while (waitpid(-1, &status, 0) && done < n_philos)
	{
		status = status >> 8;
		if (status > 0)
			finish_philo(philos, n_philos, status, &died);
		else
			done++;
	}
	i = 0;
	while (i < n_philos)
	{
		waitpid(philos[i].id, NULL, 0);
		i++;
	}
}

void	philo_bonus(t_data *data)
{
	t_fork			*forks;
	t_philo			*philos;
	t_bool			all_alive;
	sem_t			*all_alive_mtx;
	struct timeval	ab_time;

	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_ALL_ALIVE);
	init_semaphores(&forks, &all_alive_mtx, data->n_philos);
	philos = malloc(sizeof(t_philo) * data->n_philos);
	init_philos(philos, data, forks);
	all_alive = true;
	init_all_alive(philos, data->n_philos, &all_alive, all_alive_mtx);
	gettimeofday(&ab_time, NULL);
	init_philos_time(philos, data->n_philos, &ab_time);
	start_philos(philos, data->n_philos);
	wait_philos(philos, data->n_philos);
	close_semaphores(forks, all_alive_mtx);
	free(philos);
}

int	main(int argc, char **argv)
{
	t_data			*data;
	t_args_error	args_err;

	data = malloc(sizeof(t_data));
	args_err = check_args(data, argc, argv);
	if (args_err)
	{
		if (args_err == N_OF_ARGS)
			printf("ERROR: Invalid number of arguments\n");
		else if (args_err == NEGATIVE_ARGS)
			printf("ERROR: Arguments cannot be negative\n");
		else if (args_err == NO_DIGIT)
			printf("ERROR: Arguments can be digits only\n");
		else if (args_err == NUMBER_TOO_BIG)
			printf("ERROR: Argument number cannot be bigger than %d\n",
				__INT_MAX__);
		else if (args_err == NUMBER_TOO_SMALL)
			printf("ERROR: Argument number cannot be 0 or smaller\n");
		free(data);
		exit(1);
	}
	else
		philo_bonus(data);
	free(data);
	return (0);
}
