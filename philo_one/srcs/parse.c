/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 17:35:02 by memilio           #+#    #+#             */
/*   Updated: 2020/10/25 17:46:13 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		ft_parse(int argc, char **argv, t_all *all)
{
	int		i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (0); // error
	if ((all->philo_num = ft_atou(argv[1])) <= 0)
		return (0); // error
	if ((all->time_to_die = ft_atou(argv[2])) <= 0)
		return (0); // error
	if ((all->time_to_eat = ft_atou(argv[3])) <= 0)
		return (0); // error
	if ((all->time_to_sleep = ft_atou(argv[4])) <= 0)
		return (0); // error
	if (argc == 6 && ((all->eat_count = ft_atou(argv[5])) <= 0))
		return (0); // error
	return (1);
}
