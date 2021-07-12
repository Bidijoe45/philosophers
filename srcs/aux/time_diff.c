#include <sys/time.h>

int	time_diff_us(struct timeval time1, struct timeval time2)
{
	return (((time1.tv_sec - time2.tv_sec) * 1000000)
		+ (time1.tv_usec - time2.tv_usec));
}
