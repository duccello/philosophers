/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duccello <duccello@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:12:55 by duccello          #+#    #+#             */
/*   Updated: 2025/10/13 18:20:19 by duccello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

void	say_goodbye(t_dinner *settings)
{
	int	i;

	i = 0;
	while (i < settings->num_of)
	{
		if (settings->philos[i] != NULL)
		{
			pthread_mutex_destroy(&settings->philos[i]->last_meal_m);
			pthread_mutex_destroy(&settings->philos[i]->done_m);
			free(settings->philos[i]);
		}
		i++;
	}
	if (settings->philos != NULL)
		free(settings->philos);
}

void	do_the_dishes(t_dinner *settings)
{
	int	i;

	i = 0;
	while (i < settings->num_of)
	{
		if (settings->forks[i] != NULL)
		{
			pthread_mutex_destroy(&settings->forks[i]->mutex);
			free(settings->forks[i]);
		}
		i++;
	}
	if (settings->forks != NULL)
		free(settings->forks);
}

void	clean_the_table(t_dinner *settings)
{
	if (settings != NULL)
	{
		pthread_mutex_destroy(&settings->dying_m);
		pthread_mutex_destroy(&settings->printing_m);
		pthread_mutex_destroy(&settings->all_done_m);
		free(settings);
	}
}

void	bye_bye(t_dinner *settings)
{
	say_goodbye(settings);
	do_the_dishes(settings);
	clean_the_table(settings);
}
