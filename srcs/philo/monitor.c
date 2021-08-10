/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:52:26 by apavel            #+#    #+#             */
/*   Updated: 2021/08/10 15:52:51 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"
#include "../aux/aux.h"
#include "../bool.h"
#include "../log/log.h"

#include <stdio.h>
#include <stdlib.h>

t_bool	check_philo_death(t_philo *philo, struct timeval time)
{
	long int	time_diff;

	time_diff = time_diff_ms(time, philo->eat_start);
	if (time_diff >= ((philo->time_to_die_ms + 1))
		&& philo->state != UNINITIALIZED && philo->state != DONE)
	{
		return (true);
	}
	return (false);
}

void	kill_philo(t_philo *philo, struct timeval time, t_bool *all_alive)
{
	pthread_mutex_lock(philo->all_alive_mtx);
	philo_log(PHILO_DEATH, philo, time, philo->ab_time);
	*all_alive = false;
	philo_release_forks(philo);
	pthread_mutex_unlock(philo->all_alive_mtx);
}

void	check_philos(t_philo *philos, int n_philos, t_bool *all_alive)
{
	struct timeval	time;
	long int		time_diff;
	int				i;
	int				philos_done;

	philos_done = 0;
	i = 0;
	while (*all_alive)
	{
		gettimeofday(&time, NULL);
		if (check_philo_death(&philos[i], time))
		{
			kill_philo(&philos[i], time, all_alive);
			break ;
		}
		if (philos[i].state == DONE)
			philos_done++;
		if (philos_done == n_philos)
			break ;
		if (i == (n_philos - 1))
			i = 0;
		else
			i++;
		usleep(CHECK_TIME);
	}
}
