/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:20:56 by memilio           #+#    #+#             */
/*   Updated: 2020/11/03 20:19:54 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	init_philo_sem_n_start_process(t_philo *philo, int i)
{
	char		*tmp;
	pid_t		pid;

	tmp = ft_itoa_u(i);
	sem_unlink(tmp);
	philo->tag = i;
	philo->end_of_eat = sem_open(tmp, O_CREAT, 0660, 0);
	free(tmp);
	if ((pid = fork()) < 0)
	{
		ft_print_error("fork failed", NULL);
		return ;
	}
	else if (pid == 0)
	{
		simulation(philo);
		while (1)
			usleep(1000);
	}
	else
		philo->table->pid[i] = pid;
}

static void	start_threads(t_table *table)
{
	int			i;
	pthread_t	eat_thread;
	t_philo		philos[table->philo_num];
	pid_t		pid[table->philo_num];

	table->pid = pid;
	i = -1;
	while (++i < table->philo_num)
	{
		philos[i].table = table;
		philos[i].eat_count = table->eat_count;
		init_philo_sem_n_start_process(&philos[i], i);
	}
	if (pthread_create(&eat_thread, NULL, is_hungry, philos))
	{
		ft_print_error("thread failed", NULL);
		return ;
	}
	sem_wait(table->finish);
	i = -1;
	while (++i < table->philo_num)
		kill(table->pid[i], SIGKILL);
}

static int	init_sems_threads(t_table *table)
{
	if ((table->forks = sem_open("forks", O_CREAT, 0660, table->philo_num)) < 0)
		return (1);
	if ((table->death = sem_open("death", O_CREAT, 0660, 1)) < 0)
		return (1);
	if ((table->steward = sem_open("steward", O_CREAT, 0660, 1)) < 0)
		return (1);
	if ((table->output = sem_open("output", O_CREAT, 0660, 1)) < 0)
		return (1);
	if ((table->finish = sem_open("finish", O_CREAT, 0660, 0)) < 0)
		return (1);
	start_threads(table);
	sem_close(table->forks);
	sem_close(table->death);
	sem_close(table->steward);
	sem_close(table->output);
	sem_close(table->finish);
	return (0);
}

static void	unlink_sems(void)
{
	sem_unlink("forks");
	sem_unlink("steward");
	sem_unlink("death");
	sem_unlink("output");
	sem_unlink("finish");
}

int			main(int argc, char **argv)
{
	t_table		table;

	ft_init(&table);
	if (ft_parse(argc, argv, &table))
		return (1);
	unlink_sems();
	if (init_sems_threads(&table))
		return (ft_print_error("smth wrong with semaphores", NULL));
	return (0);
}
