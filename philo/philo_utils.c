/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: lstarek <lstarek@student.42vienna.com      +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2026/04/27 18:36:28 by lstarek           #+#    #+#             */
/*   Updated: 2026/04/27 18:37:15 by lstarek          ###   ########.fr       */
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
	else if (type == 3)
	{
		printf("Do not test with more than 200 philosophers!\n");
	}
	else if (type == 4)
	{
		printf("Malloch failure!\n");
	}
	return (type);
}

int	input_invalid(t_info *input)
{
	int		i;
	char	*itoaed;

	i = 1;
	input->i = 0;
	if (input->ac != 5 && input->ac != 6)
		return (quit(1));
	if (ft_atoi(input->av[1]) > 200)
		return (quit(3));
	input->threads = ft_atoi(input->av[1]);
	while (i < input->ac)
	{
		itoaed = ft_itoa(ft_atoi(input->av[i]));
		if (!itoaed)
			return(quit(4));
		if (ft_strcmp(input->av[i], itoaed))
			return (free(itoaed), quit(2));
		if (ft_atoi(input->av[i]) <= 0)
			return (free(itoaed), quit(2));
		free(itoaed);
		i++;
	}
	return (0);
}

void	destroy_everything(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->max_n)
	{
		pthread_mutex_destroy(&(philos[i].fork));
		i++;
	}
	pthread_mutex_destroy(philos->mutex);
}
