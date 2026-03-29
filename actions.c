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
#include <sys/time.h>

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
	gettimeofday(&(info->last_supper), NULL);
	printf("==%ld==\t%d is eating\n", now_ms(info), info->n);
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
