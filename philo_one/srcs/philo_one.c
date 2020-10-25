/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:20:56 by memilio           #+#    #+#             */
/*   Updated: 2020/10/25 18:00:30 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
**	Description:
**		philosopher with threads and mutex
**
**	Arguments:
**		number_of_philosophers time_to_die time_to_eat time_to_sleep \
**		[number_of_times_each_philosopher_must_eat]
**
**	External functs:
**		memset, malloc, free, write, usleep, gettimeofday, \
**		pthread_create, pthread_detach, pthread_join, \
**		pthread_mutex_init, pthread_mutex_destroy, \
**		pthread_mutex_lock, pthread_mutex_unlock
**
**	Common rules:
**		- One fork between each philosopher, therefore there will be a fork at \
**		the right and at the left of each philosopher.
**		- To avoid philosophers duplicating forks, you should protect the \
**		forks state with a mutex for each of them.
**		- Each philosopher should be a thread.
*/

void	ft_print_args(t_all *all)
{
	printf("num_philos = %d\n", all->philo_num);
	printf("time to die = %d\n", all->time_to_die);
	printf("time to eat = %d\n", all->time_to_eat);
	printf("time to sleep = %d\n", all->time_to_sleep);
	if (all->eat_count > 0)
		printf("eat count = %d\n", all->eat_count);
}

int		main(int argc, char **argv)
{
	t_all	all;

	ft_init(&all);
	if (!ft_parse(argc, argv, &all))
	{
		ft_putstr(RED"Error\nWrong input parameters!\n"ENDCOLOR);
		return (1);
	}
	ft_print_args(&all); // TEMP
	return (0);
}
