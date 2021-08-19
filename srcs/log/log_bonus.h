/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 12:40:57 by apavel            #+#    #+#             */
/*   Updated: 2021/08/19 12:40:58 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_BONUS_H
# define LOG_BONUS_H

# include <sys/time.h>
# include "../philo_bonus/philo_bonus.h"

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