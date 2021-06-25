#ifndef PHILO_H
# define PHILO_H

#include "../lib/libft/libft.h"

typedef struct s_fork
{
	int id;
	t_bool in_use;
} t_fork;

typedef enum e_pstate
{
	EATING,
	SLEEPING,
	THINKING
} t_pstate;

typedef struct s_philo
{
	int id;
	t_pstate state;
} t_philo;

typedef struct  s_data
{
	int		n_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		n_eat;
}				t_data;

void	philo_eat();

#endif