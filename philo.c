/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstarek <lstarek@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 14:37:13 by lstarek           #+#    #+#             */
/*   Updated: 2026/03/29 14:37:17 by lstarek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	quit(int type)
{
	if (type == 1)
	{
		printf("Usage: ./philo number_of_philosophers ");
		printf("time_to_die time_to_eat time_to_sleep\n");
	}
	else if (type == 2)
		printf("Args cannot be 0\n");
	return (type);
}

void	*table_activities(void *info_ptr)
{
	t_philo	*info;
	t_state	state;

	info = (t_philo *)info_ptr;
	state.have_eaten = 0;
	pthread_mutex_lock(info->mutex);
	state.n_must_eat = info[0].times_must_eat;
	state.n_philos_exist = info[0].max_n;
	pthread_mutex_unlock(info->mutex);
	state.philo_died = 0;
	while (state.have_eaten != state.n_philos_exist && !state.philo_died)
	{
		state.have_eaten = 0;
		state.i = 0;
		while (state.i < state.n_philos_exist)
		{
			pthread_mutex_lock(info->mutex);
			if (state.n_must_eat > 0
				&& (info[state.i].times_eaten >= state.n_must_eat))
				state.have_eaten += 1;
			pthread_mutex_unlock(info->mutex);
			if (is_dead(info+state.i))
			{
				state.philo_died = 1;
			}
			state.i++;
		}
		usleep(5000);
	}
	pthread_mutex_lock(info->mutex);
	while (state.i > 0)
	{
		state.i--;
		if (state.philo_died)
			printf("==%ld==\t%d died\n", now_ms(info), info[state.i].n);
		info[state.i].impending_doom = 1;
		info[state.i].game_won = 1;
	}
	if (!state.philo_died)
		printf("All philos have eated\n");
	pthread_mutex_unlock(info->mutex);
	return (NULL);
}

void	initialise(t_philo *philo, char **av, t_info *info)
{
	philo->mutex = &(info->mutex);
	philo->n = info->i + 1;
	philo->tv = &(info->tv);
	philo->max_n = info->threads;
	philo->impending_doom = 0;
	philo->times_eaten = 0;
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	gettimeofday(&(philo->last_supper), NULL);
	if (info->ac == 6)
		philo->times_must_eat = ft_atoi(av[5]);
	else
		philo->times_must_eat = -1;
	pthread_mutex_init(&(philo->fork), NULL);
}

int	main(int ac, char **av)
{
	pthread_t	*threddy;
	pthread_t	table;
	t_philo		*philos;
	t_info		info;

	info.i = 0;
	info.ac = ac;
	if (ac != 5 && ac != 6)
		return (quit(1));
	info.threads = ft_atoi(av[1]);
	if ((info.threads < 1 || ft_atoi(av[2]) < 1 || ft_atoi(av[3]) < 1
			|| ft_atoi(av[4]) < 1) || (ac == 6 && ft_atoi(av[5]) < 1))
		return (quit(2));
	pthread_mutex_init(&(info.mutex), NULL);
	threddy = malloc(sizeof(pthread_t) * info.threads);
	philos = malloc(sizeof(t_philo) * info.threads);
	gettimeofday(&(info.tv), NULL);
	pthread_mutex_lock(&(info.mutex));
	while (info.i < info.threads)
	{
		initialise(philos + info.i, av, &info);
		philos[info.i++].next_fork = &(philos[(info.i + 1) % info.threads].fork);
	}
	while (info.i > 0)
		pthread_create(&(threddy[--info.i]), NULL, &thread_init,
			&(philos[info.i]));
	pthread_create(&table, NULL, &table_activities, philos);
	pthread_mutex_unlock(&(info.mutex));
	while (info.i < info.threads)
		pthread_join(threddy[info.i++], NULL);
	return (pthread_join(table, NULL), free(philos), free(threddy), 0);
}
