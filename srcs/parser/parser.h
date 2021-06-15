#ifndef PARSER_H
# define PARSER_H

typedef enum e_parser_error
{
	no_error,
	n_of_args,
	negative_args
}			e_parser_error;

e_parser_error parse_args(int argc, char **argv);

#endif