/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstarek <lstarek@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 14:37:31 by lstarek           #+#    #+#             */
/*   Updated: 2026/03/29 14:37:33 by lstarek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	now_ms(t_philo *info)
{
	struct timeval	now;
	long			diff;

	gettimeofday(&now, NULL);
	diff = (now.tv_sec - info->tv->tv_sec) * 1000 + (now.tv_usec
			- info->tv->tv_usec) / 1000;
	return (diff);
}

int	ft_sleep(useconds_t time, t_philo *info)
{
	unsigned int	i;

	i = time / 1000;
	while (i > 0)
	{
		usleep(1000);
		i--;
		pthread_mutex_lock(info->mutex);
		if (info->impending_doom)
			return (pthread_mutex_unlock(info->mutex), 1);
		pthread_mutex_unlock(info->mutex);
	}
	return (0);
}
int	is_dead(t_philo *info)
{
	struct timeval	now;
	long			diff;

	gettimeofday(&now, NULL);
	diff = (now.tv_sec - info->last_supper.tv_sec) * 1000 + (now.tv_usec
			- info->last_supper.tv_usec) / 1000;
	return (diff > info->time_to_die);
}