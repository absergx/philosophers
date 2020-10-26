/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:20:56 by memilio           #+#    #+#             */
/*   Updated: 2020/10/26 15:56:35 by memilio          ###   ########.fr       */
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
	printf(GREEN"num_philos = %d\n", all->philo_num);
	printf("time to die = %d\n", all->time_to_die);
	printf("time to eat = %d\n", all->time_to_eat);
	printf("time to sleep = %d\n"ENDCOLOR, all->time_to_sleep);
	if (all->eat_count > 0)
		printf(GREEN"eat count = %d\n"ENDCOLOR, all->eat_count);
}

void	ft_table_init(t_table *table, int size)
{
	int		i;

	i = -1;
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * size);
	while (++i < size)
		pthread_mutex_init(&table->forks[i], NULL);
}

void	ft_philos_init(t_all *all)
{
	int		i;

	i = -1;
	all->philos = (t_philo *)malloc(sizeof(t_philo) * all->philo_num);
	while (++i < all->philo_num)
	{
		all->philos[i].tag = i + 1;
		all->philos[i].eat_num = 0;
	}
}

int		main(int argc, char **argv)
{
	t_all	all;

	ft_init(&all);
	if (ft_parse(argc, argv, &all))
		return (1);
	ft_print_args(&all); // TEMP
	ft_table_init(&all.table, all.philo_num);
	return (0);
}
