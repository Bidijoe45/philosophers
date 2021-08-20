/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 19:58:50 by apavel            #+#    #+#             */
/*   Updated: 2021/08/20 11:51:22 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "bool.h"
#include "philo_bonus.h"
#include "aux/aux.h"
#include "log/log_bonus.h"

static void	philo_get_forks(t_philo *philo)
{
	struct timeval	time;

	sem_wait(philo->forks);
	sem_wait(philo->all_alive_mtx);
	gettimeofday(&time, NULL);
	philo_log(PHILO_FORK, philo, time, philo->ab_time);
	sem_post(philo->all_alive_mtx);
	sem_wait(philo->forks);
	sem_wait(philo->all_alive_mtx);
	gettimeofday(&time, NULL);
	philo_log(PHILO_FORK, philo, time, philo->ab_time);
	sem_post(philo->all_alive_mtx);
}

void	philo_release_forks(t_philo *philo)
{
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	philo_eat(t_philo *philo)
{
	struct timeval	time;

	philo_get_forks(philo);
	sem_wait(philo->all_alive_mtx);
	gettimeofday(&time, NULL);
	gettimeofday(&philo->eat_start, NULL);
	philo_log(PHILO_EAT, philo, time, philo->ab_time);
	sem_post(philo->all_alive_mtx);
	ft_msleep(philo->time_to_eat_ms);
	philo_release_forks(philo);
	philo->state = SLEEPING;
}
