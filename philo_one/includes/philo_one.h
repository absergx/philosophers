/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:23:51 by memilio           #+#    #+#             */
/*   Updated: 2020/10/31 15:04:04 by memilio          ###   ########.fr       */
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

typedef struct		s_philo
{
	long			start_sim;
	int				tag;
	long			last_lunch;
	int				eat_count;
	t_table			*table;
}					t_philo;

/*
**		parse.c
*/

int					ft_parse(int argc, char **argv, t_table *table);
void				ft_init(t_table *table);

/*
**		utils.c
*/

char				*ft_itoa_u(unsigned long n);
int					ft_print_error(char *str, char *value);
int					ft_strlen(char *str);
void				ft_putstr(char *str);
int					ft_atou(char *str);

/*
**		simulation.c
*/

void				*simulation(void *ptr);

/*
**		simulation_utils.c
*/

void				print_message(t_philo *philo, char *str);
void				ft_wait(int time);
int					get_time(void);

#endif
