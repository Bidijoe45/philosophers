#ifndef LOG_H
# define LOG_H

# include <sys/time.h>
# include "../philo/philo.h"

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