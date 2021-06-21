#ifndef PARSER_H
# define PARSER_H

typedef enum e_parser_error
{
	NO_ERROR,
	N_OF_ARGS,
	NEGATIVE_ARGS,
	NO_DIGIT
}			t_parser_error;

t_parser_error parse_args(int argc, char **argv);

#endif