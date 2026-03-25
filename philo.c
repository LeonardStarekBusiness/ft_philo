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

void	announce(const char *msg, t_philo info)
{
	pthread_mutex_lock(info.mutex);
	printf(msg, 0, info.n);
	pthread_mutex_unlock(info.mutex);
}

void	take_fork(const t_philo info)
{
	announce("%d\t%d has taken a fork!\n", info);
	return ;
}

void	eat(const t_philo info)
{
	announce("%d\t%d is eating!\n", info);
	usleep(500000);
	return ;
}

void	start_simulation(void *info_ptr)
{
	t_philo	info;

	info = *(t_philo *)info_ptr;
	while (1)
	{
		announce("%d\t%d is thinking!\n", info);
		pthread_mutex_lock(&info.fork);
			take_fork(info);
			pthread_mutex_lock(info.next_fork);
				take_fork(info);
				eat(info);
			pthread_mutex_unlock(&info.fork);
		pthread_mutex_unlock(info.next_fork);		
		announce("%d\t%d is sleeping!\n", info);
	}
}

void	*thread_init(void *info_ptr)
{
	t_philo	info;

	info = *(t_philo *)info_ptr;

	pthread_mutex_lock(info.start);
	usleep(50);
	pthread_mutex_unlock(info.start);
	start_simulation(info_ptr);
	return (NULL);
}

int	main(int ac, char **av)
{
	int				i;
	pthread_t		*threddy;
	t_philo			*infos;
	pthread_mutex_t	mutex;
	pthread_mutex_t	start;
	int				threads;

	i = 0;
	if (ac != 5 && ac != 6)
		return (quit(0));
	threads = ft_atoi(av[1]);
	if (threads < 1 || ft_atoi(av[2]) < 1 || ft_atoi(av[3]) < 1
		|| ft_atoi(av[4]) < 1)
		return (quit(1));
	if (ac == 6 && ft_atoi(av[5]) < 1)
		return (quit(1));
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&start, NULL);
	threddy = malloc(sizeof(pthread_t) * threads);
	infos = malloc(sizeof(t_philo) * threads);
	while (i < threads)
	{
		infos[i].mutex = &mutex;
		infos[i].n = i;
		infos[i].start = &start;
		infos[i].max_n = threads;
		pthread_mutex_init(&(infos[i].fork), NULL);
		infos[i].next_fork = &(infos[(i+1)%threads].fork);
		i++;
	}
	i = 0;
	pthread_mutex_lock(&start);
	while (i < threads)
	{
		pthread_create(&(threddy[i]), NULL, &thread_init, &(infos[i]));
		i++;
	}
	usleep(500);
	pthread_mutex_unlock(&start);
	i = 0;
	while (i < threads)
	{
		pthread_join(threddy[i], NULL);
		i++;
	}
	return (0);
}
