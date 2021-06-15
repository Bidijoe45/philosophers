#ifndef PARSER_H
# define PARSER_H

#include "../philo.h"

typedef enum e_parser_error
{
	no_error,
	n_of_args,
	negative_args,
    only_digits
}			e_parser_error;

e_parser_error parse_args(t_philo *philo, int argc, char **argv);

#endif