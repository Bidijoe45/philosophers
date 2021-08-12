/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 19:59:27 by apavel            #+#    #+#             */
/*   Updated: 2021/08/12 20:03:30 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "philo_bonus.h"
#include "../aux/aux.h"
#include "../log/log_bonus.h"

void	philo_sleep(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	sem_wait(philo->all_alive_mtx);
	philo_log(PHILO_SLEEP, philo, time, philo->ab_time);
	sem_post(philo->all_alive_mtx);
	ft_msleep(philo->time_to_sleep_ms);
	philo->state = THINKING;
}
