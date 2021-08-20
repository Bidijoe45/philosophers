/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 19:58:55 by apavel            #+#    #+#             */
/*   Updated: 2021/08/20 11:52:03 by apavel           ###   ########.fr       */
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

void	kill_philo(t_philo *philo, struct timeval time)
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

void	*check_philo_death_thread(void *philo_data)
{
	struct timeval	time;
	t_philo			*philo;
	long			time_diff;

	philo = (t_philo *)philo_data;
	gettimeofday(&time, NULL);
	time_diff = time_diff_ms(philo->eat_start, time);
	while (time_diff <= (philo->time_to_die_ms + 1))
	{
		gettimeofday(&time, NULL);
		usleep(CHECK_TIME);
	}
	kill_philo(philo, time);
	return (NULL);
}
