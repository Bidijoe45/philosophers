/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:58:15 by apavel            #+#    #+#             */
/*   Updated: 2021/08/12 19:56:39 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "philo.h"
#include "../aux/aux.h"
#include "../log/log.h"

void	philo_sleep(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	pthread_mutex_lock(philo->all_alive_mtx);
	philo_log(PHILO_SLEEP, philo, time, philo->ab_time);
	pthread_mutex_unlock(philo->all_alive_mtx);
	ft_msleep(philo->time_to_sleep_ms);
	philo->state = THINKING;
}
