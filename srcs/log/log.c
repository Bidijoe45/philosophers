#include <stdio.h>
#include <sys/time.h>
#include "log.h"
#include "../philo/philo.h"
#include "../aux/aux.h"

void	philo_log(t_log_type type, t_philo *philo,
	struct timeval mtime, struct timeval ab_time)
{
	unsigned int	time;

	time = time_diff_us(mtime, ab_time) / 1000;
	
	if (type == PHILO_DEATH && *philo->all_alive)
		printf("%u %d died\n", time, philo->id);
	else if (type == PHILO_EAT && *philo->all_alive)
		printf("%u %d is eating\n", time, philo->id);
	else if (type == PHILO_SLEEP && *philo->all_alive)
		printf("%u %d is sleeping\n", time, philo->id);
	else if (type == PHILO_THINK && *philo->all_alive)
		printf("%u %d is thinking\n", time, philo->id);
	else if (type == PHILO_FORK && *philo->all_alive)
		printf("%u %d has taken a fork\n", time, philo->id);
}
