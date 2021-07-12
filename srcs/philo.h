#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include "bool.h"

typedef struct s_fork
{
	int				id;
	t_bool			in_use;
	pthread_mutex_t	mutex;
}	t_fork;

typedef enum e_pstate
{
	EATING,
	SLEEPING,
	THINKING
}	t_pstate;

typedef struct s_philo
{
	int			id;
	int			time_to_die_ms;
	int			time_to_eat_ms;
	int			time_to_sleep_ms;
	int			ntimes_to_eat;
	int			n_eat;
	int			left_fork_id;
	int			right_fork_id;
	t_pstate	state;
	pthread_t	thread;
	t_bool		*all_alive;
	t_fork		*forks;
}	t_philo;

typedef struct s_data
{
	int		n_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		ntimes_to_eat;
}				t_data;

void	philo_eat(t_philo *philo, struct timeval *ab_time);
void	philo_sleep(t_philo *philo, struct timeval *ab_time);
void	philo_think(t_philo *philo, struct timeval *ab_time);

#endif