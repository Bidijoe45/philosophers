#include <stdio.h>
#include <sys/time.h>
#include "log.h"
#include "../aux/aux.h"

void	philo_log(t_log_type type, int philo_id,
	struct timeval mtime, struct timeval ab_time)
{
	unsigned int	time;

	time = time_diff_us(mtime, ab_time);
	if (PHILO_DEATH)
		printf("%5u %d died\n", time, philo_id);
	else if (PHILO_EAT)
		printf("%5u %d is eating\n", time, philo_id);
	else if (PHILO_SLEEP)
		printf("%5u %d is sleeping\n", time, philo_id);
	else if (PHILO_THINK)
		printf("%5u %d is thinking\n", time, philo_id);
}
