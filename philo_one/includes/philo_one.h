/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:23:51 by memilio           #+#    #+#             */
/*   Updated: 2020/10/26 15:54:13 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

# define RED "\033[38;5;160m"
# define ENDCOLOR "\033[0m"
# define GREEN "\033[38;5;46m"

typedef struct		s_table
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	output_mutex;
	pthread_mutex_t	time_mutex;
}					t_table;

typedef struct		s_philo
{
	int				tag;
	int				eat_num;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
}					t_philo;

typedef struct		s_all
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	t_philo			*philos;
	t_table			table;
}					t_all;

/*
**		parse.c
*/

int					ft_parse(int argc, char **argv, t_all *all);

/*
**		utils.c
*/

int					ft_print_error(char *str, char *value);
void				ft_putstr(char *str);
void				ft_init(t_all *all);
int					ft_atou(char *str);

#endif
