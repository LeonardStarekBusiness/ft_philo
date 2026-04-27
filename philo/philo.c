/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstarek <lstarek@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:36:11 by lstarek           #+#    #+#             */
/*   Updated: 2026/04/27 18:37:06 by lstarek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*table_activities(void *philos_ptr)
{
	t_philo			*philos;
	t_state			state;
	unsigned short	i;

	philos = (t_philo *)philos_ptr;
	state.have_eaten = 0;
	i = 0;
	pthread_mutex_lock(philos->mutex);
	state.n_must_eat = philos[0].times_must_eat;
	state.n_philos_exist = philos[0].max_n;
	state.philo_died = -1;
	while (i < philos->max_n)
	{
		if (!(philos->error))
			philos[i++].started = 1;
		else
			philos[i++].started = -1;
	}
	pthread_mutex_unlock(philos->mutex);
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
	philo->started = 0;
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

void	handle_error(unsigned short error, t_info *info_ptr)
{
	info_ptr->i++;
	if (error)
	{
		printf("Thread creation failed!\n");
		info_ptr->i++;
	}
	return ;
}

int	main(int ac, char **av)
{
	pthread_t	*threddy;
	t_philo		*philos;
	t_info		info;

	info.ac = ac;
	info.av = av;
	if (input_invalid(&info))
		return (42);
	pthread_mutex_init(&(info.mutex), NULL);
	threddy = malloc(sizeof(pthread_t) * info.threads);
	philos = malloc(sizeof(t_philo) * info.threads);
	if (!threddy || !philos)
		return (free(threddy), free(philos), 42);
	philos->error = 0;
	while (info.i < info.threads)
		initialise(philos + info.i, av, &info);
	while (info.i-- > 0 && philos->error == 0)
		philos->error += pthread_create(&(threddy[info.i]), NULL, &thread_init,
				&(philos[info.i]));
	handle_error(philos->error, &info);
	table_activities(philos);
	while (info.i < info.threads)
		pthread_join(threddy[info.i++], NULL);
	return (free(philos), free(threddy), 0);
}
