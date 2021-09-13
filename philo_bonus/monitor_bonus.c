/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 19:58:55 by apavel            #+#    #+#             */
/*   Updated: 2021/09/13 12:00:48 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include "philo_bonus.h"
#include "aux/aux.h"
#include "bool.h"
#include "log/log_bonus.h"

void	sigkill_all_philos(t_philo *philos, int n_philos)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		kill(philos[i].pid, SIGKILL);
		i++;
	}
}

void	kill_philo(t_philo *philo)
{
	*philo->all_alive = false;
	philo_release_forks(philo);
	sem_close(philo->forks);
	sem_unlink(SEM_FORKS);
	sem_close(philo->all_alive_mtx);
	sem_unlink(SEM_ALL_ALIVE);
	exit(philo->id);
}

void	*check_philo_death_thread(void *philo_data)
{
	struct timeval	time;
	t_philo			*philo;
	long			time_diff;

	philo = (t_philo *)philo_data;
	gettimeofday(&time, NULL);
	time_diff = time_diff_ms(philo->eat_start, time);
	while (time_diff <= (philo->time_to_die_ms))
	{
		gettimeofday(&time, NULL);
		usleep(CHECK_TIME);
		time_diff = time_diff_ms(philo->eat_start, time);
	}
	kill_philo(philo);
	return (NULL);
}
