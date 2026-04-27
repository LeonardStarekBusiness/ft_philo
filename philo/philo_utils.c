/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstarek <lstarek@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:36:28 by lstarek           #+#    #+#             */
/*   Updated: 2026/04/27 18:37:15 by lstarek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_it_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	ft_atoi(const char *str)
{
	int	i;
	int	minus_counter;
	int	sum;

	i = 0;
	minus_counter = 0;
	sum = 0;
	while (is_it_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		minus_counter = (str[i] == '-');
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		sum = (sum * 10) + (str[i] - 48);
		i++;
	}
	if (minus_counter == 1)
		return (-sum);
	else
		return (sum);
}

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
