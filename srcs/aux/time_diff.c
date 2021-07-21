#include <sys/time.h>

static unsigned long int abs(long long int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

unsigned long int	time_diff_us(struct timeval time1, struct timeval time2)
{
	return abs( (time1.tv_sec * 1000000 + time1.tv_usec) - (time2.tv_sec * 1000000 + time2.tv_usec) );
}
