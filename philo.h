#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

int					ft_atoi(const char *str);

typedef struct s_table
{
	pthread_t		thread;
	char			*haveEaten;
	int				n_of_philos;
}					t_table;

typedef struct s_philo
{
	pthread_t		thread;
	short				n;
	short				max_n;

	struct timeval	*tv;
	useconds_t		time_to_die;
	useconds_t		time_to_eat;
	useconds_t		time_to_sleep;

	pthread_mutex_t	*mutex;
	pthread_mutex_t	fork;
	pthread_mutex_t	*next_fork;

	struct timeval	*last_supper;
	short			times_must_eat;
	short			times_eaten;
	char			impending_doom;

	t_table			*table;
}					t_philo;



#endif // PHILO_H
