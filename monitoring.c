/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duccello <duccello@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:15:08 by duccello          #+#    #+#             */
/*   Updated: 2025/10/13 18:22:05 by duccello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdio.h>

bool	done(t_dinner *setting)
{
	int	i;
	int	eating_count;

	i = 0;
	eating_count = 0;
	while (i < setting->num_of)
	{
		pthread_mutex_lock(&setting->philos[i]->done_m);
		if (setting->philos[i]->done == true)
			eating_count++;
		pthread_mutex_unlock(&setting->philos[i]->done_m);
		if (eating_count == setting->num_of)
		{
			pthread_mutex_lock(&setting->all_done_m);
			setting->all_done = true;
			pthread_mutex_unlock(&setting->all_done_m);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	dead(t_dinner *setting)
{
	int	i;
	int	hunger;

	i = 0;
	hunger = 0;
	while (i < setting->num_of)
	{
		pthread_mutex_lock(&setting->philos[i]->last_meal_m);
		hunger = timestamp(setting->philos[i]) - setting->philos[i]->last_meal;
		pthread_mutex_unlock(&setting->philos[i]->last_meal_m);
		if (hunger >= setting->time_to_die)
		{
			pthread_mutex_lock(&setting->dying_m);
			setting->dead = true;
			pthread_mutex_unlock(&setting->dying_m);
			pthread_mutex_lock(&setting->printing_m);
			printf("%ld %d died\n", timestamp(setting->philos[i]),
				setting->philos[i]->num);
			pthread_mutex_unlock(&setting->printing_m);
			return (true);
		}
		i++;
	}
	return (false);
}
