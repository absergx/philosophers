/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:20:56 by memilio           #+#    #+#             */
/*   Updated: 2020/10/31 14:00:11 by memilio          ###   ########.fr       */
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
**
**	Forks handling:
**		pthread_mutex_lock(&all->table.fork[i])
**		pthread_mutex_lock(&all->table.fork[(i + 1) % all->philo_num])
**	блокировка двух вилок с учетом, что последний берет первую вилку
*/

void	init_n_start_threads(t_table *table)
{
	int						i;
	t_philo					philos[table->philo_num];
	pthread_t				threads[table->philo_num];
	
	i = -1;
	while (++i < table->philo_num)
	{
		philos->tag = i;
		philos->table = table;
		philos->eat_count = table->eat_count;
		pthread_create(&threads[i], NULL, simulation, &philos[i]);
	}
	i = -1;
	while (++i < table->philo_num)
		pthread_join(threads[i], NULL);
	i = -1;
	while (++i < table->philo_num)
		pthread_mutex_destroy(&table->forks[i]);
}

void	ft_table_init(t_table *table)
{
	int						i;
	pthread_mutex_t			forks[table->philo_num];
	static pthread_mutex_t	death_mutex = PTHREAD_MUTEX_INITIALIZER;
	static pthread_mutex_t	output_mutex = PTHREAD_MUTEX_INITIALIZER;
	static pthread_mutex_t	time_mutex = PTHREAD_MUTEX_INITIALIZER;

	i = -1;
	table->forks = forks;
	while (++i < table->philo_num)
		pthread_mutex_init(&table->forks[i], NULL);
	table->forks = forks;
	table->output_mutex = output_mutex;
	table->time_mutex = time_mutex;
	table->death_mutex = death_mutex;
	init_n_start_threads(table);
	pthread_mutex_destroy(&death_mutex);
	pthread_mutex_destroy(&time_mutex);
	pthread_mutex_destroy(&output_mutex);
}

int		main(int argc, char **argv)
{
	t_table					table;

	ft_init(&table);
	if (ft_parse(argc, argv, &table))
		return (1);
	ft_table_init(&table);
	return (0);
}
