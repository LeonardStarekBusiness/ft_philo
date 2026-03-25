#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int					ft_atoi(const char *str);

typedef struct s_philo
{
	pthread_t		thread;
	int				n;
	int				max_n;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*start;
	pthread_mutex_t fork;
	pthread_mutex_t *next_fork;
}					t_philo;

#endif // PHILO_H
