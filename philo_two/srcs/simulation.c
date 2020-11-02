/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:04:59 by memilio           #+#    #+#             */
/*   Updated: 2020/11/02 14:35:50 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		handle_forks(t_philo *philo)
{
	sem_wait(philo->table->steward);
	sem_wait(philo->table->forks);
	if (philo->table->died)
	{
		sem_post(philo->table->steward);
		sem_post(philo->table->forks);
		return (1);
	}
	print_message(philo, MAGENTA"has taken a fork\n"ENDCOLOR);
	if (philo->table->philo_num == 1)
	{
		while (!philo->table->died)
			usleep(10);
		return (1);
	}
	sem_wait(philo->table->forks);
	if (philo->table->died)
	{
		sem_post(philo->table->steward);
		sem_post(philo->table->forks);
		return (1);
	}
	print_message(philo, MAGENTA"has taken a fork\n"ENDCOLOR);
	sem_post(philo->table->steward);
	return (0);
}

void	get_forks(t_philo *philo)
{
	if (handle_forks(philo))
		return ;
	if (philo->table->died)
	{
		sem_post(philo->table->forks);
		sem_post(philo->table->forks);
		return ;
	}
	print_message(philo, GREEN"is eating\n"ENDCOLOR);
	philo->eat_count -= 1;
	sem_wait(philo->table->time);
	philo->last_lunch = get_time();
	sem_post(philo->table->time);
	ft_wait(philo->table->time_to_eat);
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
}

void	*is_dead(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo *)ptr;
	sem_wait(philo->table->time);
	while (get_time() - philo->last_lunch <= philo->table->time_to_die)
	{
		sem_post(philo->table->time);
		usleep(10);
		sem_wait(philo->table->time);
	}
	sem_post(philo->table->time);
	if (!philo->eat_count)
		return (NULL);
	sem_wait(philo->table->death);
	if (philo->table->died)
	{
		sem_post(philo->table->death);
		return (NULL);
	}
	print_message(philo, RED"is died\n"ENDCOLOR);
	philo->table->died = 1;
	sem_post(philo->table->death);
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
