#include "parser.h"
#include "../aux/aux.h"

t_args_error	check_argument(char *arg)
{
	int i;

	i = 0;
	while (arg[i])
	{	
		if (arg[i] == '-')
			return (NEGATIVE_ARGS);
		if (!ft_isdigit(arg[i]))
			return (NO_DIGIT);
		i++;
	}

	return (NO_ERROR);
}

void	parse_arg(t_data *data, int n_arg, char *arg)
{
	//TODO: QUITAR LIBFR!!!
	if (n_arg == 1)
		data->n_philos = ft_atoi(arg);
	else if (n_arg == 2)
		data->time_to_die = ft_atoi(arg);
	else if (n_arg == 3)
		data->time_to_eat = ft_atoi(arg);
	else if (n_arg == 4)
		data->time_to_sleep = ft_atoi(arg);
	else if (n_arg == 5)
		data->n_eat = ft_atoi(arg);
}

t_args_error check_args(t_data *data, int argc, char **argv)
{
	int i;
	t_args_error parser_err;
	
	if (argc < 5 || argc > 6)
		return (N_OF_ARGS);
	i = 1;
	parser_err = NO_ERROR;
	while (argv[i])
	{
		parser_err = check_argument(argv[i]);
		if (parser_err != NO_ERROR)
			return (parser_err);
		parse_arg(data, i, argv[i]);
		i++;
	}
	return (parser_err);
}