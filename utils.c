/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duccello <duccello@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:20:36 by duccello          #+#    #+#             */
/*   Updated: 2025/10/13 18:26:59 by duccello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>

long	timestamp(t_philos *philos)
{
	struct timeval	tv;
	long			timestamp;

	gettimeofday(&tv, NULL);
	timestamp = (tv.tv_sec * MILISECONDS) + (tv.tv_usec / MILISECONDS)
		- philos->s->starting_time;
	return (timestamp);
}

bool	numeric_args(char **argv)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

long	ft_atol(const char *p)
{
	long	charge;
	long	num;
	long	temp;

	charge = 1;
	num = 0;
	temp = 0;
	while (*p == ' ' || (*p >= '\t' && *p <= '\r'))
		p++;
	if (*p == '+' || *p == '-')
	{
		if (*p == '-')
			charge = charge * -1;
		p++;
	}
	while (*p)
	{
		if (!(*p >= '0' && *p <= '9'))
			return (-2147483649);
		temp = (*p - '0');
		num = temp + (num * 10);
		p++;
	}
	return (num * charge);
}

bool	check(t_dinner *setting)
{
	pthread_mutex_lock(&setting->all_done_m);
	pthread_mutex_lock(&setting->dying_m);
	if (setting->all_done == true || setting->dead == true)
	{
		pthread_mutex_unlock(&setting->dying_m);
		pthread_mutex_unlock(&setting->all_done_m);
		return (false);
	}
	pthread_mutex_unlock(&setting->dying_m);
	pthread_mutex_unlock(&setting->all_done_m);
	return (true);
}

void	drop_them_forks(t_philos *philos)
{
	pthread_mutex_unlock(&philos->r_fork->mutex);
	pthread_mutex_unlock(&philos->l_fork->mutex);
}
