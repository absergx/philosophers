/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:04:59 by memilio           #+#    #+#             */
/*   Updated: 2020/11/03 15:12:40 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
	sem_wait(philo->table->output);
	print_message(philo, MAGENTA"has taken a fork\n"ENDCOLOR);
	sem_post(philo->table->output);
	sem_wait(philo->table->forks);
	if (philo->table->died)
	{
		sem_post(philo->table->steward);
		sem_post(philo->table->forks);
		return (1);
	}
	sem_wait(philo->table->output);
	print_message(philo, MAGENTA"has taken a fork\n"ENDCOLOR);
	sem_post(philo->table->output);
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
	sem_wait(philo->table->output);
	print_message(philo, GREEN"is eating\n"ENDCOLOR);
	sem_post(philo->table->output);
	philo->eat_count -= 1;
	philo->last_lunch = get_time();
	ft_wait(philo->table->time_to_eat);
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
}

void	*is_dead(void *ptr)
{
	t_philo		*philo;
	int			time;

	philo = (t_philo *)ptr;
	time = get_time();
	while (time - philo->last_lunch <= philo->table->time_to_die)
	{
		time = get_time();
		usleep(10);
	}
	if (!philo->eat_count)
	{
		sem_post(philo->end_of_eat);
		return (NULL);
	}
	sem_wait(philo->table->death);
	sem_wait(philo->table->output);
	print_message(philo, RED"is died\n"ENDCOLOR);
	philo->table->died = 1;
	sem_post(philo->table->finish);
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
		sem_wait(philo->table->output);
		print_message(philo, BLUE"is sleeping\n"ENDCOLOR);
		sem_post(philo->table->output);
		ft_wait(philo->table->time_to_sleep);
		if (philo->table->died)
			break ;
		sem_wait(philo->table->output);
		print_message(philo, YELLOW"is thinking\n"ENDCOLOR);
		sem_post(philo->table->output);
	}
	pthread_join(death_time, NULL);
	return (NULL);
}
