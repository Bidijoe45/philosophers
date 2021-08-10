#include <stdlib.h>
#include "philo.h"
#include "../log/log.h"

void	philo_die_waiting(t_philo *philo, struct timeval time, struct timeval ab_time)
{
    pthread_mutex_lock(philo->all_alive_mtx);
    philo_log(PHILO_DEATH, philo, time, ab_time);
    *philo->all_alive = false;
    pthread_mutex_unlock(philo->all_alive_mtx);
}

void	philo_die_eating(t_philo *philo, struct timeval time, struct timeval ab_time)
{
    pthread_mutex_lock(philo->all_alive_mtx);
    philo_log(PHILO_DEATH, philo, time, ab_time);
    *philo->all_alive = false;
    philo_release_forks(philo);
    pthread_mutex_unlock(philo->all_alive_mtx);
}