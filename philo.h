#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

int					ft_atoi(const char *str);

typedef struct s_philo
{
	pthread_t		thread;
	int				n;
	int				max_n;

	struct timeval	*tv;
	useconds_t		time_to_die;
	useconds_t		time_to_eat;
	useconds_t		time_to_sleep;
	
	pthread_mutex_t	*mutex;
	pthread_mutex_t fork;
	pthread_mutex_t *next_fork;

	struct timeval	*last_supper;
	char			*impending_doom;
}					t_philo;

#endif // PHILO_H
