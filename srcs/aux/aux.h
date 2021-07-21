#ifndef AUX_H
# define AUX_H

# include <sys/time.h>

int	ft_atoi(const char *str);
int	ft_isdigit(int c);
long long int	time_diff_us(struct timeval time1, struct timeval time2);

#endif