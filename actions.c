#include "philo.h"

long	now_ms(t_philo *info)
{
	struct timeval	now;
	long			diff;

	gettimeofday(&now, NULL);
	diff = (now.tv_sec - info->tv->tv_sec) * 1000 + (now.tv_usec
			- info->tv->tv_usec) / 1000;
	return (diff);
}

void	take_fork(t_philo *info)
{
	pthread_mutex_lock(info->mutex);
	printf("==%ld==\t%d has taken a fork!\n", now_ms(info), info->n);
	//usleep(5000);
	pthread_mutex_unlock(info->mutex);
}

void	think(t_philo *info)
{
	pthread_mutex_lock(info->mutex);
	printf("==%ld==\t%d is thinking!\n", now_ms(info), info->n);
	//usleep(5000);
	pthread_mutex_unlock(info->mutex);
}

void	eat(t_philo *info)
{
	pthread_mutex_lock(info->mutex);
	printf("==%ld==\t%d is eating!\n", now_ms(info), info->n);
	//usleep(5000);
	info->times_eaten++;
	pthread_mutex_unlock(info->mutex);
	usleep(info->time_to_eat * 1000);
}

void	nap(t_philo *info)
{
	pthread_mutex_lock(info->mutex);
	printf("==%ld==\t%d is sleeping!\n", now_ms(info), info->n);
	//usleep(5000);
	pthread_mutex_unlock(info->mutex);
	usleep(info->time_to_sleep * 1000);
}