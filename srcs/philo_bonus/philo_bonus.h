/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 19:58:43 by apavel            #+#    #+#             */
/*   Updated: 2021/08/12 20:09:11 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <sys/time.h>
# include "../bool.h"
# include "../data.h"

# define SEM_FORKS "forks_3"
# define SEM_ALL_ALIVE "all_alive_3"
# define CHECK_TIME 300

typedef sem_t	t_fork;

typedef enum e_pstate
{
	UNINITIALIZED,
	DONE,
	EATING,
	SLEEPING,
	THINKING
}	t_pstate;

typedef struct s_philo
{
	int				id;
	pid_t			pid;
	int				time_to_die_ms;
	int				time_to_eat_ms;
	int				time_to_sleep_ms;
	int				ntimes_to_eat;
	int				n_eat;
	t_pstate		state;
	t_fork			*forks;
	t_bool			*all_alive;
	sem_t			*all_alive_mtx;
	struct timeval	eat_start;
	struct timeval	ab_time;
}	t_philo;

void	philo_eat(t_philo *philo);
void	philo_release_forks(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	init_philos(t_philo *philos, t_data *data, t_fork *forks);
void	init_all_alive(t_philo *philos, int n_philos, t_bool *all_alive,
			sem_t *all_alive_mtx);
void	init_philos_time(t_philo *philos, int n_philos,
			struct timeval *ab_time);
void	init_semaphores(t_fork **forks, sem_t **all_alive_mtx, int n_philos);
void	start_philos(t_philo *philos, int n_philos);
void	wait_philos(void);
void	philo_process(t_philo *philo_data);
void	*check_philo_death_thread(void *philo_data);
void	sigkill_all_philos(t_philo *philos, int n_philos);
t_philo	*alloc_philos(int n_philos);

#endif