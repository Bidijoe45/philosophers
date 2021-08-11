/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:58:47 by apavel            #+#    #+#             */
/*   Updated: 2021/08/10 18:36:43 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include "philo.h"
#include "../log/log.h"

void	philo_think(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	pthread_mutex_lock(philo->all_alive_mtx);
	philo_log(PHILO_THINK, philo, time, philo->ab_time);
	pthread_mutex_unlock(philo->all_alive_mtx);
	philo->state = EATING;
}
