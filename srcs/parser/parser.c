#include "parser.h"
#include "../philo.h"
#include "../../lib/libft/libft.h"

#include <stdio.h>

e_parser_error	check_argument(char *arg)
{
	int i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '-')
			return (negative_args);
		else if (!ft_isdigit(arg[i]))
        {
			return (only_digits);
        }
		i++;
	}

	return (no_error);
}

void parse_argument(t_philo *philo, int pos, char *arg)
{
    printf("arg: %s\n", arg);
	if (pos == 1)
		philo->n_philos = ft_atoi(arg);
	else if (pos == 2)
		philo->time_to_die = ft_atoi(arg);
	else if (pos == 3)
		philo->time_to_eat = ft_atoi(arg);
	else if (pos == 4)
		philo->time_to_sleep = ft_atoi(arg);
	else if (pos == 5)
		philo->n_eat = ft_atoi(arg);
}

e_parser_error parse_args(t_philo *philo, int argc, char **argv)
{
	int i;
	e_parser_error parser_err;
	
	if (argc < 5 || argc > 6)
		return (n_of_args);

	i = 1;
	parser_err = no_error;
	while (argv[i])
	{
		parser_err = check_argument(argv[i]);
		if (parser_err != no_error)
			return (parser_err);
		parse_argument(philo, i, argv[i]);
		i++;
	}

	return (parser_err);
}