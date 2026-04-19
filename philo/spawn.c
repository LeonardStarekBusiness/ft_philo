/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstarek <lstarek@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 14:37:25 by lstarek           #+#    #+#             */
/*   Updated: 2026/03/29 14:37:27 by lstarek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	simulation_ongoing(t_philo *info)
{
	return (info->times_must_eat == -1
		|| info->times_eaten < info->times_must_eat);
}

void	start_simulation_leftist(t_philo *info)
{
	pthread_mutex_lock(&(info->fork));
	take_fork(info);
	pthread_mutex_lock(info->next_fork);
	take_fork(info);
	if (eat(info))
	{
		pthread_mutex_unlock(&(info->fork));
		pthread_mutex_unlock(info->next_fork);
		return ;
	}
	pthread_mutex_unlock(info->next_fork);
	pthread_mutex_unlock(&(info->fork));
	if (nap(info))
		return ;
	think(info);
	pthread_mutex_lock(info->mutex);
	if (info->impending_doom)
		return ((void)pthread_mutex_unlock(info->mutex));
	pthread_mutex_unlock(info->mutex);
	if (!(info->n == 1 || info->n == info->max_n) && info->max_n % 2)
		usleep(1000);
	if (simulation_ongoing(info))
		start_simulation_leftist(info);
}

void	start_simulation_rightist(t_philo *info)
{
	pthread_mutex_lock(info->next_fork);
	take_fork(info);
	pthread_mutex_lock(&(info->fork));
	take_fork(info);
	if (eat(info))
	{
		pthread_mutex_unlock(info->next_fork);
		pthread_mutex_unlock(&(info->fork));
		return ;
	}
	pthread_mutex_unlock(&(info->fork));
	pthread_mutex_unlock(info->next_fork);
	if (nap(info))
		return ;
	think(info);
	pthread_mutex_lock(info->mutex);
	if (info->impending_doom)
		return ((void)pthread_mutex_unlock(info->mutex));
	pthread_mutex_unlock(info->mutex);
	if (!(info->n == 1 || info->n == info->max_n) && info->max_n % 2)
		usleep(1000);
	if (simulation_ongoing(info))
		start_simulation_rightist(info);
}

void	start_simulation_single(t_philo *info)
{
	pthread_mutex_unlock(info->mutex);
	printf("==%ld==\t%d has taken a fork\n", now_ms(info), info->n);
	usleep(info->time_to_die);
	pthread_mutex_unlock(info->mutex);
}

void	*thread_init(void *info_ptr)
{
	t_philo	*info;

	info = (t_philo *)info_ptr;
	pthread_mutex_lock(info->mutex);
	pthread_mutex_unlock(info->mutex);
	if (info->max_n == 1)
		start_simulation_single(info);
	else if ((info->n) % 2)
		start_simulation_rightist(info);
	else
		start_simulation_leftist(info);
	return (NULL);
}
