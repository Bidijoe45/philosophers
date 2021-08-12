/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:59:03 by apavel            #+#    #+#             */
/*   Updated: 2021/08/12 19:57:00 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "philo.h"

void	start_philos(t_philo *philos, int n_philos)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		pthread_create(&(philos[i].thread), NULL, philo_thread, &(philos[i]));
		i += 2;
	}
	usleep(1000);
	i = 1;
	while (i < n_philos)
	{
		pthread_create(&(philos[i].thread), NULL, philo_thread, &(philos[i]));
		i += 2;
	}
}

void	join_philos(t_philo *philos, int n_philos)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

void	*philo_thread(void *philo_data)
{
	t_philo			*philo;

	philo = (t_philo *)philo_data;
	philo->state = EATING;
	while (*philo->all_alive)
	{
		if (philo->state == EATING)
		{
			philo_eat(philo);
			philo->n_eat++;
			if (philo->n_eat == philo->ntimes_to_eat)
			{
				philo->state = DONE;
				break ;
			}
		}
		else if (philo->state == SLEEPING)
			philo_sleep(philo);
		else if (philo->state == THINKING)
			philo_think(philo);
	}
	return (NULL);
}
