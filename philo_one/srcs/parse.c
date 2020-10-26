/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 17:35:02 by memilio           #+#    #+#             */
/*   Updated: 2020/10/26 15:27:58 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		ft_parse(int argc, char **argv, t_all *all)
{
	if (argc < 5 || argc > 6)
		return (ft_print_error("Wrong number of arguments", NULL));
	if ((all->philo_num = ft_atou(argv[1])) <= 0)
		return (ft_print_error("Wrong number of Philosophers", argv[1]));
	if ((all->time_to_die = ft_atou(argv[2])) <= 0)
		return (ft_print_error("Wrong time to die", argv[2]));
	if ((all->time_to_eat = ft_atou(argv[3])) <= 0)
		return (ft_print_error("Wrong time to eat", argv[3]));
	if ((all->time_to_sleep = ft_atou(argv[4])) <= 0)
		return (ft_print_error("Wrong time to sleep", argv[4]));
	if (argc == 6 && ((all->eat_count = ft_atou(argv[5])) <= 0))
		return (ft_print_error("Wrong number of times each philosopher must \
eat", argv[5]));
	return (0);
}
