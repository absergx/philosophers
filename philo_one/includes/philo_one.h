/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:23:51 by memilio           #+#    #+#             */
/*   Updated: 2020/10/30 20:40:04 by memilio          ###   ########.fr       */
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
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	int				died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	output_mutex;
	pthread_mutex_t	time_mutex;
}					t_table;

typedef struct		s_all
{
	int				simul_start;
	int				tag;
	int				last_lunch;
	int				eat_num;
	t_table			*table;
}					t_all;

/*
**		parse.c
*/

int					ft_parse(int argc, char **argv, t_table *table);
void				ft_init(t_table *table);

/*
**		utils.c
*/

int					ft_print_error(char *str, char *value);
void				ft_putstr(char *str);
int					ft_atou(char *str);

#endif
