/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 12:40:48 by apavel            #+#    #+#             */
/*   Updated: 2021/08/20 11:41:55 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_H
# define LOG_H

# include <sys/time.h>
# include "../philo.h"

typedef enum e_log_type
{
	PHILO_DEATH,
	PHILO_EAT,
	PHILO_SLEEP,
	PHILO_THINK,
	PHILO_FORK
}	t_log_type;

void	philo_log(t_log_type type, t_philo *philo, struct timeval time,
			struct timeval ab_time);

#endif