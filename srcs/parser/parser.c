#include "parser.h"

e_parser_error	check_argument(char *arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '-')
			return (negative_args);
		i++;
	}

	return (no_error);
}

e_parser_error parse_args(int argc, char **argv)
{
	int i;
	e_parser_error parser_err;
	
	if (argc < 5 || argc > 6)
		return (n_of_args);

	i = 0;
	parser_err = no_error;
	while (argv[i])
	{
		parser_err = check_argument(argv[i]);
		if (parser_err != no_error)
			return (parser_err);
		i++;
	}

	return (parser_err);
}