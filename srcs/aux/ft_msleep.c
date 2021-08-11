#include <sys/time.h>
#include <unistd.h>
#include "aux.h"

void ft_msleep(unsigned int ms)
{
	struct timeval time;
	struct timeval itime;

	gettimeofday(&time, NULL);
	gettimeofday(&itime, NULL);

	while (time_diff_ms(itime, time) < ms)
	{
		gettimeofday(&time, NULL);
		usleep(SLEEP_TIME);
	}
} 