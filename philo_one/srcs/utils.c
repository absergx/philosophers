/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 17:21:00 by memilio           #+#    #+#             */
/*   Updated: 2020/11/01 17:04:51 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

char	*ft_itoa_u(unsigned long n)
{
	unsigned long	tmp;
	char			*res;
	size_t			len;

	len = 1;
	tmp = n;
	while (tmp >= 10)
	{
		tmp /= 10;
		++len;
	}
	if (!(res = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	res[len] = '\0';
	while (len != 0)
	{
		res[len - 1] = n % 10 + '0';
		n /= 10;
		--len;
	}
	return (res);
}

int		ft_print_error(char *str, char *value)
{
	int		i;

	i = 0;
	while (str[i])
		++i;
	write(2, RED, ft_strlen(RED));
	write(2, "Error\n", 6);
	write(2, str, i);
	if (value)
	{
		i = 0;
		while (value[i])
			++i;
		write(2, ": ", 2);
		write(2, value, i);
	}
	write(2, "\n", 1);
	write(2, ENDCOLOR, ft_strlen(ENDCOLOR));
	return (1);
}

int		ft_strlen(char *str)
{
	int		len;

	len = 0;
	while (str[len])
		++len;
	return (len);
}

int		ft_atou(char *str)
{
	long	res;
	int		i;

	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		res *= 10;
		res += str[i] - '0';
		if (res > 2147483647)
			break ;
		++i;
	}
	return (str[i] == '\0' ? res : -1);
}
