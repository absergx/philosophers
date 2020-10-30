/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 17:35:02 by memilio           #+#    #+#             */
/*   Updated: 2020/10/30 20:21:09 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		ft_parse(int argc, char **argv, t_table *table)
{
	if (argc < 5 || argc > 6)
		return (ft_print_error("Wrong number of arguments", NULL));
	if ((table->philo_num = ft_atou(argv[1])) <= 0)
		return (ft_print_error("Wrong number of Philosophers", argv[1]));
	else if (table->philo_num > 200)
		return (ft_print_error("Number of Philosophers should be <= 200", argv[1]));
	if ((table->time_to_die = ft_atou(argv[2])) <= 0)
		return (ft_print_error("Wrong time to die", argv[2]));
	if ((table->time_to_eat = ft_atou(argv[3])) <= 0)
		return (ft_print_error("Wrong time to eat", argv[3]));
	if ((table->time_to_sleep = ft_atou(argv[4])) <= 0)
		return (ft_print_error("Wrong time to sleep", argv[4]));
	if (argc == 6 && ((table->eat_count = ft_atou(argv[5])) <= 0))
		return (ft_print_error("Wrong number of times each philosopher must eat", argv[5]));
	return (0);
}
