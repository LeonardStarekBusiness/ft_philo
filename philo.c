#include "philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <sys/time.h>

int	quit(int type)
{
	if (!type)
	{
		write(1, "Usage: ./philo number_of_philosophers ", 39);
		write(1, "time_to_die time_to_eat time_to_sleep\n", 39);
	}
	else if (type == 1)
		write(1, "Args cannot be 0\n", 18);
	return (-1);
}

long now_ms(t_philo *info)
{
	struct timeval	now;
	long			diff;

	gettimeofday(&now, NULL);
	diff = now.tv_usec - info->tv->tv_usec;
	return (diff);
}

void	start_simulation(t_philo *info)
{
	while (1)
	{
		pthread_mutex_lock(info->mutex);
			printf("%ld\t%d is thinking!\n", now_ms(info), info->n);
			usleep(500000);
		pthread_mutex_unlock(info->mutex);
		pthread_mutex_lock(&(info->fork));
			pthread_mutex_lock(info->mutex);
				printf("%ld\t%d has taken a fork!\n", now_ms(info), info->n);
				usleep(500000);
				pthread_mutex_unlock(info->mutex);
			pthread_mutex_lock(info->next_fork);
				pthread_mutex_lock(info->mutex);
					printf("%ld\t%d has taken a fork!\n", now_ms(info), info->n);
					usleep(500000);
					pthread_mutex_unlock(info->mutex);
				pthread_mutex_lock(info->mutex);
					printf("%ld\t%d is eating!\n", now_ms(info), info->n);
					usleep(500000);
					pthread_mutex_unlock(info->mutex);
				usleep(500000);
				pthread_mutex_lock(info->mutex);
					printf("%ld\t%d is sleeping!\n", now_ms(info), info->n);
					usleep(500000);
					pthread_mutex_unlock(info->mutex);
			pthread_mutex_unlock(info->next_fork);
		pthread_mutex_unlock(&(info->fork));
	}
}

void	*thread_init(void *info_ptr)
{
	t_philo	*info;

	info = (t_philo *)info_ptr;

	pthread_mutex_lock(info->mutex);
	printf("%d\t%d has spawned!\n", 0, info->n);
	pthread_mutex_unlock(info->mutex);

	while (!info->hasStarted)
		usleep(500);
	usleep(500000);
	start_simulation(info);
	return (NULL);
}

int	main(int ac, char **av)
{
	int				i;
	int				started;
	pthread_t		*threddy;
	t_philo			*infos;
	pthread_mutex_t	mutex;
	int				threads;
	struct timeval	tv;

	i = 0;
	started = 0;
	if (ac != 5 && ac != 6)
		return (quit(0));
	threads = ft_atoi(av[1]);
	if (threads < 1 || ft_atoi(av[2]) < 1 || ft_atoi(av[3]) < 1
		|| ft_atoi(av[4]) < 1)
		return (quit(1));
	if (ac == 6 && ft_atoi(av[5]) < 1)
		return (quit(1));
	pthread_mutex_init(&mutex, NULL);
	threddy = malloc(sizeof(pthread_t) * threads);
	infos = malloc(sizeof(t_philo) * threads);
	gettimeofday(&tv, NULL);
	while (i < threads)
	{
		infos[i].mutex = &mutex;
		infos[i].hasStarted = &started;
		infos[i].n = i;
		infos[i].tv = &tv;
		infos[i].max_n = threads;
		pthread_mutex_init(&(infos[i].fork), NULL);
		infos[i].next_fork = &(infos[(i+1)%threads].fork);
		i++;
	}
	i = 0;
	while (i < threads)
	{
		pthread_create(&(threddy[i]), NULL, &thread_init, &(infos[i]));
		i++;
	}
	started = 1;
	i = 0;
	while (i < threads)
	{
		pthread_join(threddy[i], NULL);
		i++;
	}
	return (0);
}
