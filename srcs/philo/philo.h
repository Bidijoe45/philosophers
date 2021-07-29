#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include "../bool.h"
# include "../data.h"

# define SLEEP_TIME 4000

typedef struct s_fork
{
	int				id;
	t_bool			in_use;
	pthread_mutex_t	mutex;
}	t_fork;

typedef enum e_pstate
{
	UNINITIALIZED,
	EATING,
	SLEEPING,
	THINKING
}	t_pstate;

typedef struct s_philo
{
	int				id;
	int				time_to_die_ms;
	int				time_to_eat_ms;
	int				time_to_sleep_ms;
	int				ntimes_to_eat;
	int				n_eat;
	int				left_fork_id;
	int				right_fork_id;
	t_pstate		state;
	pthread_t		thread;
	t_fork			*forks;
	t_bool			*all_alive;
	pthread_mutex_t	*all_alive_mtx;
	struct timeval	eat_start;
}	t_philo;

int		philo_eat(t_philo *philo, struct timeval *ab_time);
void	philo_release_forks(t_philo *philo);
int		philo_sleep(t_philo *philo, struct timeval *ab_time);
void	philo_think(t_philo *philo, struct timeval *ab_time);
void	philo_die_eating(t_philo *philo, struct timeval time, struct timeval ab_time);
void	philo_die_waiting(t_philo *philo, struct timeval time, struct timeval ab_time);
void	init_forks(t_fork *forks, int n_philos);
void	init_philos(t_philo *philos, t_data *data, t_fork *forks);
void	init_all_alive(t_philo *philos, int n_philos, t_bool *all_alive, 
						pthread_mutex_t *all_alive_mtx);
void	start_philos(t_philo *philos, int n_philos);
void	join_philos(t_philo *philos, int n_philos);
void	*philo_thread(void *philo_data);
t_philo *alloc_philos(int n_philos);

#endif