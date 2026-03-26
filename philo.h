#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table
{
	pthread_t		thread;
	char			*haveEaten;
	int				n_of_philos;
}					t_table;

typedef struct s_state
{
	int		i;
	int		have_eaten;
	int		n_must_eat;
	int		n_philos_exist;
} t_state;

typedef struct s_philo
{
	pthread_t		thread;
	short			n;
	short			max_n;

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

typedef struct s_info
{
	pthread_mutex_t	mutex;
	int				i;
	struct timeval	tv;
	int				threads;
	int				ac;
}					t_info;

int					ft_atoi(const char *str);

long				now_ms(t_philo *info);
void				take_fork(t_philo *info);
void				think(t_philo *info);
void				eat(t_philo *info);
void				nap(t_philo *info);

#endif // PHILO_H
