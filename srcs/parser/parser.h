#ifndef PARSER_H
# define PARSER_H

# include "../data.h"

typedef enum e_args_error
{
	NO_ERROR = 0,
	N_OF_ARGS = 1,
	NEGATIVE_ARGS = 2,
	NO_DIGIT = 3
}			t_args_error;

t_args_error	check_args(t_data *data, int argc, char **argv);

#endif