/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstarek <lstarek@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 14:36:53 by lstarek           #+#    #+#             */
/*   Updated: 2026/03/29 14:36:55 by lstarek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int				i;
	int				have_eaten;
	int				n_must_eat;
	int				n_philos_exist;
	int				philo_died;
}					t_state;

typedef struct s_philo
{
	pthread_t		thread;
	short			n;
	short			max_n;

	struct timeval	*tv;
	struct timeval	last_supper;
	useconds_t		time_to_die;
	useconds_t		time_to_eat;
	useconds_t		time_to_sleep;

	pthread_mutex_t	*mutex;
	pthread_mutex_t	fork;
	pthread_mutex_t	*next_fork;

	short			times_must_eat;
	short			times_eaten;
	char			impending_doom;
	char			game_won;

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
int					is_dead(t_philo *info);

void				take_fork(t_philo *info);
void				think(t_philo *info);
int					eat(t_philo *info);
int					nap(t_philo *info);

void				start_simulation_leftist(t_philo *info);
void				start_simulation_rightist(t_philo *info);
void				*thread_init(void *info_ptr);

int					ft_sleep(useconds_t time, t_philo *info);

#endif // PHILO_H
