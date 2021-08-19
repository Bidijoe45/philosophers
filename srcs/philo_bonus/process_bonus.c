/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 19:59:23 by apavel            #+#    #+#             */
/*   Updated: 2021/08/19 12:34:04 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "philo_bonus.h"
#include "../aux/aux.h"

void	start_philos_i(t_philo *philos, int n_philos, int index_start)
{
	int		i;
	pid_t	pid;

	i = index_start;
	while (i < n_philos)
	{
		pid = fork();
		philos[i].pid = pid;
		if (pid == 0)
		{
			philo_process(&philos[i]);
			exit(0);
		}
		i += 2;
	}
}

void	start_philos(t_philo *philos, int n_philos)
{
	start_philos_i(philos, n_philos, 0);
	usleep(1000);
	start_philos_i(philos, n_philos, 1);
}

void	wait_philos(t_philo *philos, int n_philos)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		waitpid(philos[i].pid, 0, 0);
		i++;
	}
}

void	philo_process(t_philo *philo)
{
	pthread_t		death_check_thread;

	philo->state = EATING;
	pthread_create(&death_check_thread, NULL, &check_philo_death_thread, philo);
	while (*philo->all_alive)
	{
		if (philo->state == EATING)
		{
			philo_eat(philo);
			philo->n_eat++;
			if (philo->n_eat == philo->ntimes_to_eat)
			{
				philo->state = DONE;
				exit(0);
			}
		}
		else if (philo->state == SLEEPING)
			philo_sleep(philo);
		else if (philo->state == THINKING)
			philo_think(philo);
	}
}
