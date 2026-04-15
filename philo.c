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
		printf("time_to_die time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
	}
	else if (type == 2)
	{
		printf("Args must be positive integers\n");
	}
	return (type);
}

int	input_invalid(t_info *input)
{
	input->i = 0;
	if (input->ac != 5 && input->ac != 6)
		return (quit(1));
	input->threads = ft_atoi(input->av[1]);
	if ((input->threads < 1 || ft_atoi(input->av[2]) < 1
			|| ft_atoi(input->av[3]) < 1 || ft_atoi(input->av[4]) < 1)
		|| (input->ac == 6 && ft_atoi(input->av[5]) < 1))
		return (quit(2));
	return (0);
}

void	*table_activities(void *philos_ptr)
{
	t_philo	*philos;
	t_state	state;

	philos = (t_philo *)philos_ptr;
	state.have_eaten = 0;
	pthread_mutex_lock(philos->mutex);
	state.n_must_eat = philos[0].times_must_eat;
	state.n_philos_exist = philos[0].max_n;
	pthread_mutex_unlock(philos->mutex);
	state.philo_died = -1;
	while (state.have_eaten < state.n_philos_exist && (state.philo_died == -1))
		check_if_eated(philos, &state);
	pthread_mutex_lock(philos->mutex);
	kill_philos(philos, &state);
	pthread_mutex_unlock(philos->mutex);
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
	philo->last_supper = 0;
	if (info->ac == 6)
		philo->times_must_eat = ft_atoi(av[5]);
	else
		philo->times_must_eat = -1;
	pthread_mutex_init(&(philo->fork), NULL);
	gettimeofday(&(info->tv), NULL);
	if ((info->i) + 1 == info->threads)
		philo->next_fork = &((philo - (info->i))->fork);
	else
		philo->next_fork = &((philo + 1)->fork);
	info->i++;
}

int	main(int ac, char **av)
{
	pthread_t	*threddy;
	pthread_t	table;
	t_philo		*philos;
	t_info		info;

	info.ac = ac;
	info.av = av;
	if (input_invalid(&info))
		return (42);
	pthread_mutex_init(&(info.mutex), NULL);
	threddy = malloc(sizeof(pthread_t) * info.threads);
	philos = malloc(sizeof(t_philo) * info.threads);
	pthread_mutex_lock(&(info.mutex));
	while (info.i < info.threads)
		initialise(philos + info.i, av, &info);
	while (info.i > 0)
		pthread_create(&(threddy[--info.i]), NULL, &thread_init,
			&(philos[info.i]));
	pthread_create(&table, NULL, &table_activities, philos);
	pthread_mutex_unlock(&(info.mutex));
	while (info.i < info.threads)
		pthread_join(threddy[info.i++], NULL);
	return (pthread_join(table, NULL), free(philos), free(threddy), 0);
}
