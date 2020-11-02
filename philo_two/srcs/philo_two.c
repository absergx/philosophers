/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:20:56 by memilio           #+#    #+#             */
/*   Updated: 2020/11/02 13:21:01 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

/*
**				SEMAPHORES
**	1. sem_unlink("name") - unlunk old semaphores
**	2. sem_open("name", O_CREAT, 0660, 1) - open semaphores
**	3. sem_close(name) - close semaphores (without "")
**
**	sem_post - increment semaphore by 1
**	sem_wait - decrement semaphore by 1
*/

void	start_threads(t_table *table)
{
	int			i;
	pthread_t	threads[table->philo_num];
	t_philo		philos[table->philo_num];

	i = -1;
	while (++i < table->philo_num)
	{
		philos[i].tag = i;
		philos[i].table = table;
		philos[i].eat_count = table->eat_count;
		if (pthread_create(&threads[i], NULL, simulation, &philos[i]))
			return ;
	}
	i = -1;
	while (++i < table->philo_num)
		if (pthread_join(threads[i], NULL))
			return ;
}

int		init_sems_threads(t_table *table)
{
	sem_unlink("forks");
	sem_unlink("steward");
	sem_unlink("death");
	sem_unlink("output");
	sem_unlink("time");
	if ((table->forks = sem_open("forks", O_CREAT, 0660, table->philo_num)) < 0)
		return (1);
	if ((table->death = sem_open("death", O_CREAT, 0660, 1)) < 0)
		return (1);
	if ((table->steward = sem_open("steward", O_CREAT, 0660, 1)) < 0)
		return (1);
	if ((table->output = sem_open("output", O_CREAT, 0660, 1)) < 0)
		return (1);
	if ((table->time = sem_open("time", O_CREAT, 0660, 1)) < 0)
		return (1);
	start_threads(table);
	sem_close(table->forks);
	sem_close(table->death);
	sem_close(table->steward);
	sem_close(table->output);
	sem_close(table->time);
	return (0);
}

int		main(int argc, char **argv)
{
	t_table		table;

	ft_init(&table);
	if (ft_parse(argc, argv, &table))
		return (1);
	if (init_sems_threads(&table))
		return (ft_print_error("Smth wrong with semaphores", NULL));
	return (0);
}
