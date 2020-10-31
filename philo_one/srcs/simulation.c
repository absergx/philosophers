/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 13:59:30 by memilio           #+#    #+#             */
/*   Updated: 2020/10/31 20:26:28 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		handle_forks(t_philo *philo, int l_fork, int r_fork)
{
	pthread_mutex_lock(&philo->table->forks[l_fork]);
	if (philo->table->died)
	{
		pthread_mutex_unlock(&philo->table->forks[l_fork]);
		return (1);
	}
	print_message(philo, MAGENTA"has taken a fork\n"ENDCOLOR);
	if (philo->table->philo_num == 1)
	{
		while (!philo->table->died)
			usleep(10);
		return (1);
	}
	pthread_mutex_lock(&philo->table->forks[r_fork]);
	if (philo->table->died)
	{
		pthread_mutex_unlock(&philo->table->forks[l_fork]);
		pthread_mutex_unlock(&philo->table->forks[r_fork]);
		return (1);
	}
	print_message(philo, MAGENTA"has taken a fork\n"ENDCOLOR);
	return (0);
}

void	get_forks(t_philo *philo)
{
	int			r_fork;
	int			l_fork;

	l_fork = philo->tag;
	r_fork = (philo->tag + 1) % philo->table->philo_num;
	if (philo->tag % 2 == 0 && handle_forks(philo, l_fork, r_fork))
		return ;
	else if (philo->tag % 2 != 0 && handle_forks(philo, r_fork, l_fork))
		return ;
	if (philo->table->died)
	{
		pthread_mutex_unlock(&philo->table->forks[l_fork]);
		pthread_mutex_unlock(&philo->table->forks[r_fork]);
		return ;
	}
	print_message(philo, GREEN"is eating\n"ENDCOLOR);
	philo->eat_count -= 1;
	pthread_mutex_lock(&philo->table->time_mutex);
	philo->last_lunch = get_time();
	pthread_mutex_unlock(&philo->table->time_mutex);
	ft_wait(philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->table->forks[l_fork]);
	pthread_mutex_unlock(&philo->table->forks[r_fork]);
}

void	*is_dead(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->table->time_mutex);
	while (get_time() - philo->last_lunch <= philo->table->time_to_die)
	{
		pthread_mutex_unlock(&philo->table->time_mutex);
		usleep(10);
		pthread_mutex_lock(&philo->table->time_mutex);
	}
	pthread_mutex_unlock(&philo->table->time_mutex);
	if (!philo->eat_count)
		return (NULL);
	pthread_mutex_lock(&philo->table->death_mutex);
	if (philo->table->died)
	{
		pthread_mutex_unlock(&philo->table->death_mutex);
		return (NULL);
	}
	print_message(philo, RED"is died\n"ENDCOLOR);
	philo->table->died = 1;
	pthread_mutex_unlock(&philo->table->death_mutex);
	return (NULL);
}

void	*simulation(void *ptr)
{
	t_philo		*philo;
	pthread_t	death_time;

	philo = (t_philo *)ptr;
	philo->start_sim = get_time();
	philo->last_lunch = get_time();
	pthread_create(&death_time, NULL, is_dead, philo);
	while (philo->eat_count)
	{
		if (philo->table->died)
			break ;
		get_forks(philo);
		if (philo->table->died)
			break ;
		print_message(philo, BLUE"is sleeping\n"ENDCOLOR);
		ft_wait(philo->table->time_to_sleep);
		if (philo->table->died)
			break ;
		print_message(philo, YELLOW"is thinking\n"ENDCOLOR);
	}
	pthread_join(death_time, NULL);
	return (NULL);
}
