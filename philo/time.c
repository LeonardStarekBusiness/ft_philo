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

char	ft_sleep(useconds_t time, t_philo *info)
{
	unsigned int	i;
	unsigned int	j;

	i = time / 1000000;
	j = time % 1000000;
	while (i > 0)
	{
		pthread_mutex_lock(info->mutex);
		if (info->impending_doom)
			return (pthread_mutex_unlock(info->mutex), 1);
		pthread_mutex_unlock(info->mutex);
		sleep(1);
		i--;
	}
	usleep(j);
	return (0);
}

char	is_dead(t_philo *info)
{
	long	now;
	char	is_dead;

	pthread_mutex_lock(info->mutex);
	now = now_ms(info);
	is_dead = (now - info->last_supper) > info->time_to_die;
	pthread_mutex_unlock(info->mutex);
	return (is_dead);
}

void	kill_philos(t_philo *philos, t_state *state)
{
	state->i = philos->max_n;
	while (state->i > 0)
	{
		state->i--;
		if (state->philo_died == state->i)
			printf("%ld %d died\n", now_ms(philos), state->philo_died + 1);
		philos[state->i].impending_doom = 1;
		philos[state->i].game_won = 1;
	}
	if (state->philo_died == -1)
		printf("All philos have eated\n");
}
