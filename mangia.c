/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mangia.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duccello <duccello@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:15:08 by duccello          #+#    #+#             */
/*   Updated: 2025/10/13 18:22:05 by duccello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static bool	take_forks_in_order(t_philos *philos);

void	*mangia_ragazzi(t_dinner *setting)
{
	int	i;

	i = 0;
	while (i < setting->num_of)
	{
		if (pthread_create(&setting->philos[i]->thread, NULL, &bon_apetit,
				setting->philos[i]) != 0)
			return (NULL);
		i++;
	}
	while (done(setting) != true)
	{
		if (dead(setting) == true)
			break ;
		usleep(1 * MILISECONDS);
	}
	i = 0;
	while (i < setting->num_of)
	{
		pthread_join(setting->philos[i]->thread, NULL);
		i++;
	}
	return (NULL);
}

void	*bon_apetit(void *arg)
{
	t_philos	*philos;

	philos = (t_philos *)arg;
	if (philos->num % VIP_GUEST == false)
		usleep(philos->s->time_to_eat * MILISECONDS / 2);
	while (1 && philos->rounds != 0)
	{
		if (philos->num % VIP_GUEST == false)
			usleep(MILISECONDS / 2);
		if (check(philos->s) == false)
			break ;
		if (take_forks_in_order(philos) == false)
			break ;
		if (eating(philos) == false)
			break ;
		if (sleeping(philos) == false)
			break ;
		if (thinking(philos) == false)
			break ;
	}
	return (NULL);
}

static bool	take_forks_in_order(t_philos *philos)
{
	if (philos->l_fork > philos->r_fork)
	{
		if (take_forks(philos, philos->l_fork, philos->r_fork) == false)
			return (false);
	}
	else
	{
		if (take_forks(philos, philos->r_fork, philos->l_fork) == false)
			return (false);
	}
	return (true);
}
