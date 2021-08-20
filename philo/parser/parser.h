/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 12:44:50 by apavel            #+#    #+#             */
/*   Updated: 2021/08/20 11:45:45 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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