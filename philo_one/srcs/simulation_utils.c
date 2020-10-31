/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 13:59:40 by memilio           #+#    #+#             */
/*   Updated: 2020/10/31 19:31:22 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

char	*make_message(char *time, char *tag, char *str, int len)
{
	char	*res;
	int		i;
	int		res_i;

	if (!(res = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	i = 0;
	res_i = 0;
	while (time[i])
		res[res_i++] = time[i++];
	res[res_i++] = ' ';
	i = 0;
	while (tag[i])
		res[res_i++] = tag[i++];
	res[res_i++] = ' ';
	i = 0;
	while (str[i])
		res[res_i++] = str[i++];
	res[res_i] = '\0';
	return (res);
}

void	print_message(t_philo *philo, char *str)
{
	char	*time;
	char	*tag;
	char	*complete_msg;
	int		act_time;
	int		complete_msg_len;

	pthread_mutex_lock(&philo->table->output_mutex);
	if (philo->table->died)
	{
		pthread_mutex_unlock(&philo->table->output_mutex);
		return ;
	}
	act_time = get_time() - philo->start_sim;
	time = ft_itoa_u(act_time);
	tag = ft_itoa_u(philo->tag + 1);
	complete_msg_len = ft_strlen(time) + ft_strlen(tag) + ft_strlen(str) + 3;
	complete_msg = make_message(time, tag, str, complete_msg_len);
	write(1, complete_msg, complete_msg_len - 1);
	free(time);
	free(tag);
	free(complete_msg);
	pthread_mutex_unlock(&philo->table->output_mutex);
}

void	ft_wait(int time)
{
	int				start;
	int				stop;
	int				diff;

	start = get_time();
	stop = get_time();
	diff = stop - start;
	while (diff < time)
	{
		stop = get_time();
		diff = stop - start;
		usleep(10);
	}
}

int		get_time(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((int)(((current.tv_sec) * 1000) + ((current.tv_usec) / 1000)));
}
