/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 17:21:00 by memilio           #+#    #+#             */
/*   Updated: 2020/10/26 15:27:15 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		ft_print_error(char *str, char *value)
{
	int		i;

	i = 0;
	while (str[i])
		++i;
	ft_putstr(RED);
	write(2, "Error\n", 6);
	write(2, str, i);
	if (value)
	{
		i = 0;
		while (value[i])
			++i;
		write(2, ": ", 2);
		write(2, value, i);
	}
	write(2, "\n", 1);
	ft_putstr(ENDCOLOR);
	return (1);
}

void	ft_putstr(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		++i;
	write(1, str, i);
}

void	ft_init(t_all *all)
{
	all->philo_num = 0;
	all->time_to_die = 0;
	all->time_to_eat = 0;
	all->time_to_sleep = 0;
	all->eat_count = -1;
	all->philos = NULL;
}

int		ft_atou(char *str)
{
	int		res;
	int		i;

	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		res *= 10;
		res += str[i] - '0';
		++i;
	}
	return (str[i] == '\0' ? res : -1);
}
