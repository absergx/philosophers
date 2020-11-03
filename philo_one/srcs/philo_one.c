/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:20:56 by memilio           #+#    #+#             */
/*   Updated: 2020/11/03 19:53:07 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	ft_init(t_table *table)
{
	table->philo_num = 0;
	table->time_to_die = 0;
	table->time_to_eat = 0;
	table->time_to_sleep = 0;
	table->eat_count = -1;
	table->died = 0;
}

static int	ft_parse(int argc, char **argv, t_table *table)
{
	char	*msg;

	if (argc < 5 || argc > 6)
		return (ft_print_error("Wrong number of arguments", NULL));
	if ((table->philo_num = ft_atou(argv[1])) <= 0)
		return (ft_print_error("Wrong number of Philosophers", argv[1]));
	else if (table->philo_num > 200)
	{
		msg = "Number of Philosophers should be <= 200";
		return (ft_print_error(msg, argv[1]));
	}
	if ((table->time_to_die = ft_atou(argv[2])) <= 0)
		return (ft_print_error("Wrong time to die", argv[2]));
	if ((table->time_to_eat = ft_atou(argv[3])) <= 0)
		return (ft_print_error("Wrong time to eat", argv[3]));
	if ((table->time_to_sleep = ft_atou(argv[4])) <= 0)
		return (ft_print_error("Wrong time to sleep", argv[4]));
	if (argc == 6 && ((table->eat_count = ft_atou(argv[5])) <= 0))
	{
		msg = "Wrong number of times each philosopher must eat";
		return (ft_print_error(msg, argv[5]));
	}
	return (0);
}

static void	init_n_start_threads(t_table *table)
{
	int			i;
	t_philo		philos[table->philo_num];
	pthread_t	threads[table->philo_num];

	i = -1;
	while (++i < table->philo_num)
	{
		philos[i].tag = i;
		philos[i].table = table;
		philos[i].eat_count = table->eat_count;
		pthread_create(&threads[i], NULL, simulation, &philos[i]);
	}
	i = -1;
	while (++i < table->philo_num)
		pthread_join(threads[i], NULL);
	i = -1;
	while (++i < table->philo_num)
		pthread_mutex_destroy(&table->forks[i]);
}

static void	ft_table_init(t_table *table)
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

int			main(int argc, char **argv)
{
	t_table	table;

	ft_init(&table);
	if (ft_parse(argc, argv, &table))
		return (1);
	ft_table_init(&table);
	return (0);
}
