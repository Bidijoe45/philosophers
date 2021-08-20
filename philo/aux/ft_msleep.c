/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 12:39:45 by apavel            #+#    #+#             */
/*   Updated: 2021/08/19 12:39:46 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include "aux.h"

void	ft_msleep(unsigned int ms)
{
	struct timeval	time;
	struct timeval	itime;

	gettimeofday(&time, NULL);
	gettimeofday(&itime, NULL);
	while (time_diff_ms(itime, time) < ms)
	{
		gettimeofday(&time, NULL);
		usleep(SLEEP_TIME);
	}
}
