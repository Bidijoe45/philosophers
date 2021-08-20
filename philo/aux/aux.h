/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 12:39:36 by apavel            #+#    #+#             */
/*   Updated: 2021/08/19 12:39:39 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUX_H
# define AUX_H

# include <sys/time.h>

# define SLEEP_TIME 300

long int			ft_atoli(const char *str);
int					ft_isdigit(int c);
void				ft_msleep(unsigned int ms);
unsigned long int	time_diff_ms(struct timeval time1, struct timeval time2);

#endif