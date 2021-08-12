#ifndef PARSER_H
# define PARSER_H

# include "../data.h"

typedef enum e_args_error
{
	NO_ERROR = 0,
	N_OF_ARGS,
	NEGATIVE_ARGS,
	NO_DIGIT,
	NUMBER_TOO_BIG,
	NUMBER_TOO_SMALL
}			t_args_error;

t_args_error	check_args(t_data *data, int argc, char **argv);

#endif