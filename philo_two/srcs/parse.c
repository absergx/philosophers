/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 17:35:02 by memilio           #+#    #+#             */
/*   Updated: 2020/10/31 19:45:07 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_init(t_table *table)
{
	table->philo_num = 0;
	table->time_to_die = 0;
	table->time_to_eat = 0;
	table->time_to_sleep = 0;
	table->eat_count = -1;
	table->died = -1;
}

int		ft_parse(int argc, char **argv, t_table *table)
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
