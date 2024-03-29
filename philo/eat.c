/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:52:20 by apavel            #+#    #+#             */
/*   Updated: 2021/08/20 11:48:06 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "bool.h"
#include "philo.h"
#include "aux/aux.h"
#include "log/log.h"

void	get_left_fork(t_philo *philo)
{
	struct timeval	time;

	pthread_mutex_lock(&philo->forks[philo->left_fork_id - 1]);
	pthread_mutex_lock(philo->all_alive_mtx);
	gettimeofday(&time, NULL);
	philo_log(PHILO_FORK, philo, time, philo->ab_time);
	pthread_mutex_unlock(philo->all_alive_mtx);
	pthread_mutex_lock(&philo->forks[philo->right_fork_id - 1]);
	pthread_mutex_lock(philo->all_alive_mtx);
	gettimeofday(&time, NULL);
	philo_log(PHILO_FORK, philo, time, philo->ab_time);
	pthread_mutex_unlock(philo->all_alive_mtx);
}

void	get_right_fork(t_philo *philo)
{
	struct timeval	time;

	pthread_mutex_lock(&philo->forks[philo->right_fork_id - 1]);
	pthread_mutex_lock(philo->all_alive_mtx);
	gettimeofday(&time, NULL);
	philo_log(PHILO_FORK, philo, time, philo->ab_time);
	pthread_mutex_unlock(philo->all_alive_mtx);
	pthread_mutex_lock(&philo->forks[philo->left_fork_id - 1]);
	pthread_mutex_lock(philo->all_alive_mtx);
	gettimeofday(&time, NULL);
	philo_log(PHILO_FORK, philo, time, philo->ab_time);
	pthread_mutex_unlock(philo->all_alive_mtx);
}

void	philo_get_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		get_right_fork(philo);
	else
		get_left_fork(philo);
}

void	philo_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->forks[philo->left_fork_id - 1]);
	pthread_mutex_unlock(&philo->forks[philo->right_fork_id - 1]);
}

void	philo_eat(t_philo *philo)
{
	struct timeval	time;

	philo_get_forks(philo);
	pthread_mutex_lock(philo->all_alive_mtx);
	gettimeofday(&time, NULL);
	gettimeofday(&philo->eat_start, NULL);
	philo_log(PHILO_EAT, philo, time, philo->ab_time);
	pthread_mutex_unlock(philo->all_alive_mtx);
	ft_msleep(philo->time_to_eat_ms);
	philo_release_forks(philo);
	philo->state = SLEEPING;
}
