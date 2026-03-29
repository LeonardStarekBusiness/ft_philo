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

void	start_simulation_leftist(t_philo *info)
{
	while (1)
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
		pthread_mutex_unlock(&(info->fork));
		pthread_mutex_unlock(info->next_fork);
		if (nap(info))
			return ;
		think(info);
		pthread_mutex_lock(info->mutex);
		if (info->impending_doom)
			break ;
		pthread_mutex_unlock(info->mutex);
	}
	pthread_mutex_unlock(info->mutex);
}

void	start_simulation_rightist(t_philo *info)
{
	while (1)
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
		pthread_mutex_unlock(info->next_fork);
		pthread_mutex_unlock(&(info->fork));
		if (nap(info))
			return ;
		think(info);
		pthread_mutex_lock(info->mutex);
		if (info->impending_doom)
			break ;
		pthread_mutex_unlock(info->mutex);
	}
	pthread_mutex_unlock(info->mutex);
}

void	*thread_init(void *info_ptr)
{
	t_philo	*info;

	info = (t_philo *)info_ptr;
	pthread_mutex_lock(info->mutex);
	pthread_mutex_unlock(info->mutex);
	if (info->n % 2)
		start_simulation_leftist(info);
	else
		start_simulation_rightist(info);
	return (NULL);
}
