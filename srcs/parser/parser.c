#include "parser.h"
#include "../aux/aux.h"

void init_data(t_data *data)
{
	data->n_philos = -1;
	data->time_to_die = -1;
	data->time_to_eat = -1;
	data->time_to_sleep = -1;
	data->ntimes_to_eat = -1;
}

t_args_error	check_argument(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{	
		if (arg[i] == '-')
			return (NEGATIVE_ARGS);
		else if (!ft_isdigit(arg[i]))
			return (NO_DIGIT);
		i++;
	}
	return (NO_ERROR);
}

void	set_arg(t_data *data, int n_arg, int val)
{
	if (n_arg == 1)
		data->n_philos = val;
	else if (n_arg == 2)
		data->time_to_die = val;
	else if (n_arg == 3)
		data->time_to_eat = val;
	else if (n_arg == 4)
		data->time_to_sleep = val;
	else if (n_arg == 5)
		data->ntimes_to_eat = val;
}

t_args_error	parse_arg(t_data *data, int n_arg, char *arg)
{
	long long int val;

	val = ft_atoli(arg);
	if (val > __INT_MAX__)
		return (NUMBER_TOO_BIG);
	else if (val <= 0)
		return (NUMBER_TOO_SMALL);
	else
		set_arg(data, n_arg, val);
	return (NO_ERROR);
}

t_args_error	check_args(t_data *data, int argc, char **argv)
{
	int				i;
	t_args_error	parser_err;

	init_data(data);
	if (argc < 5 || argc > 6)
		return (N_OF_ARGS);
	i = 1;
	parser_err = NO_ERROR;
	while (argv[i])
	{
		parser_err = check_argument(argv[i]);
		if (parser_err != NO_ERROR)
			return (parser_err);
		parser_err = parse_arg(data, i, argv[i]);
		if (parser_err != NO_ERROR)
			return (parser_err);
		i++;
	}
	return (parser_err);
}
