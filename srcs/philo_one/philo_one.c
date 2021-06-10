#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>

#include "../philo.h"

int main(int argc, char **argv)
{
	t_philo *philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
	{
		perror(strerror(errno));
		exit(errno);
	}
		
	if (parse_args(argc, argv) == 0)
	{
		printf("Invalid args");
	}


	free(philo);
	return (0);
}

