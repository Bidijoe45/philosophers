#include "parser.h"
#include "../../lib/libft/libft.h"

t_parser_error	check_argument(char *arg)
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

t_parser_error parse_args(int argc, char **argv)
{
	int i;
	t_parser_error parser_err;
	
	if (argc < 5 || argc > 6)
		return (N_OF_ARGS);

	i = 1;
	parser_err = NO_ERROR;
	while (argv[i])
	{
		parser_err = check_argument(argv[i]);
		if (parser_err != NO_ERROR)
			return (parser_err);
		i++;
	}

	return (parser_err);
}