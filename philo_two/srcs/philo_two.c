/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:20:56 by memilio           #+#    #+#             */
/*   Updated: 2020/11/01 17:52:33 by memilio          ###   ########.fr       */
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

int		main(int argc, char **argv)
{
	t_table		table;

	ft_init(&table);
	if (ft_parse(argc, argv, &table))
		return (1);
	return (0);
}
