#ifndef LOG_H
# define LOG_H

# include <sys/time.h>

typedef enum e_log_type
{
	PHILO_DEATH,
	PHILO_EAT,
	PHILO_SLEEP,
	PHILO_THINK
}	t_log_type;

void	philo_log(t_log_type type, int philo_id, struct timeval time,
			struct timeval ab_time);

#endif