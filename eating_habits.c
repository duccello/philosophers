/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_habits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duccello <duccello@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:12:55 by duccello          #+#    #+#             */
/*   Updated: 2025/10/13 18:20:19 by duccello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

bool	take_forks(t_philos *philos, t_forks *first, t_forks *second)
{
	pthread_mutex_lock(&first->mutex);
	if (check(philos->s) == false)
	{
		pthread_mutex_unlock(&first->mutex);
		return (false);
	}
	pthread_mutex_lock(&philos->s->printing_m);
	printf("%ld %d has taken a fork\n", timestamp(philos), philos->num);
	pthread_mutex_unlock(&philos->s->printing_m);
	if (second == NULL)
	{
		pthread_mutex_unlock(&first->mutex);
		return (false);
	}
	pthread_mutex_lock(&second->mutex);
	if (check(philos->s) == false)
	{
		pthread_mutex_unlock(&second->mutex);
		pthread_mutex_unlock(&first->mutex);
		return (false);
	}
	pthread_mutex_lock(&philos->s->printing_m);
	printf("%ld %d has taken a fork\n", timestamp(philos), philos->num);
	pthread_mutex_unlock(&philos->s->printing_m);
	return (true);
}

bool	eating(t_philos *philos)
{
	if (check(philos->s) == false)
	{
		drop_them_forks(philos);
		return (false);
	}
	pthread_mutex_lock(&philos->s->printing_m);
	pthread_mutex_lock(&philos->last_meal_m);
	printf("%ld %d is eating\n", timestamp(philos), philos->num);
	philos->last_meal = timestamp(philos);
	pthread_mutex_unlock(&philos->last_meal_m);
	pthread_mutex_unlock(&philos->s->printing_m);
	philos->rounds--;
	if (philos->rounds == 0)
	{
		pthread_mutex_lock(&philos->done_m);
		philos->done = true;
		pthread_mutex_unlock(&philos->done_m);
		drop_them_forks(philos);
		return (false);
	}
	usleep(philos->s->time_to_eat * MILISECONDS);
	drop_them_forks(philos);
	return (true);
}

bool	sleeping(t_philos *philos)
{
	if (check(philos->s) == false)
		return (false);
	pthread_mutex_lock(&philos->s->printing_m);
	printf("%ld %d is sleeping\n", timestamp(philos), philos->num);
	pthread_mutex_unlock(&philos->s->printing_m);
	usleep(philos->s->time_to_sleep * MILISECONDS);
	return (true);
}

bool	thinking(t_philos *philos)
{
	if (check(philos->s) == false)
		return (false);
	pthread_mutex_lock(&philos->s->printing_m);
	printf("%ld %d is thinking\n", timestamp(philos), philos->num);
	pthread_mutex_unlock(&philos->s->printing_m);
	return (true);
}
