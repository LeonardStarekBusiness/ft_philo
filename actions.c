/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstarek <lstarek@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 14:36:59 by lstarek           #+#    #+#             */
/*   Updated: 2026/03/29 14:37:09 by lstarek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *info)
{
	pthread_mutex_lock(info->mutex);
	if (info->impending_doom)
	{
		pthread_mutex_unlock(info->mutex);
		return ;
	}
	printf("==%ld==\t%d has taken a fork\n", now_ms(info), info->n);
	pthread_mutex_unlock(info->mutex);
}

void	think(t_philo *info)
{
	pthread_mutex_lock(info->mutex);
	if (info->impending_doom)
	{
		pthread_mutex_unlock(info->mutex);
		return ;
	}
	printf("==%ld==\t%d is thinking\n", now_ms(info), info->n);
	pthread_mutex_unlock(info->mutex);
}

int	eat(t_philo *info)
{
	pthread_mutex_lock(info->mutex);
	if (info->impending_doom)
		return (pthread_mutex_unlock(info->mutex), 1);
	printf("==%ld==\t%d is eating\n", now_ms(info), info->n);
	info->last_supper = now_ms(info);
	info->times_eaten++;
	pthread_mutex_unlock(info->mutex);
	if (ft_sleep(info->time_to_eat * 1000, info))
		return (1);
	return (0);
}

int	nap(t_philo *info)
{
	pthread_mutex_lock(info->mutex);
	if (info->impending_doom)
		return (pthread_mutex_unlock(info->mutex), 1);
	printf("==%ld==\t%d is sleeping\n", now_ms(info), info->n);
	pthread_mutex_unlock(info->mutex);
	if (ft_sleep(info->time_to_eat * 1000, info))
		return (1);
	return (0);
}

void	check_if_eated(t_philo *philos, t_state *state)
{
	state->have_eaten = 0;
	state->i = 0;
	while (state->i < state->n_philos_exist)
	{
		pthread_mutex_lock(philos->mutex);
		if (state->n_must_eat > 0
			&& (philos[state->i].times_eaten >= state->n_must_eat))
			state->have_eaten += 1;
		pthread_mutex_unlock(philos->mutex);
		if (is_dead(&philos[state->i]))
			state->philo_died = state->i;
		state->i++;
	}
	usleep(5000);
}
