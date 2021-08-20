/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_diff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 12:38:05 by apavel            #+#    #+#             */
/*   Updated: 2021/08/19 12:39:16 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

unsigned long int	ft_abs(long int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

unsigned long int	time_diff_ms(struct timeval time1, struct timeval time2)
{
	return (ft_abs((time1.tv_sec * 1000 + time1.tv_usec / 1000)
			- (time2.tv_sec * 1000 + time2.tv_usec / 1000)));
}
