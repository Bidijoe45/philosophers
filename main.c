#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>


void	*print_message(void *sleep_time)
{
	int	sleep_t;

	sleep_t = *((int *)sleep_time);
	printf("Thread start | sleep time: %d\n", sleep_t);
	sleep(sleep_t);
	printf("Thread end\n");
}

int	main()
{
	pthread_t	thread_1;
	pthread_t	thread_2;

	int	tret1;
	int	tret2;
	
	int *time = malloc(sizeof(int));
	int	*time2 = malloc(sizeof(int));
	*time = 5;
	tret1 = pthread_create(&thread_1, NULL, print_message, time);


	*time2 = 2;
	tret2 = pthread_create(&thread_2, NULL, print_message, time2);
	
	pthread_join(thread_2, NULL);
	pthread_join(thread_1, NULL);

	printf("Main end\n");

	return (0);
}
