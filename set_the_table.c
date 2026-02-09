/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_the_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duccello <duccello@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:18:17 by duccello          #+#    #+#             */
/*   Updated: 2025/10/13 18:26:58 by duccello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

static t_forks	**cutlery(t_dinner *setting);
static t_philos	**arrive(t_dinner *setting);
static void		gather_around(t_philos *philos, int i, t_dinner *setting);
static int		converting_parameters(t_dinner *setting, int argc, char **argv);

int	set_the_table(t_dinner *setting, int argc, char **argv)
{
	struct timeval	tv;

	if (converting_parameters(setting, argc, argv) == 1)
	{
		printf("I would never be born\n");
		return (1);
	}
	gettimeofday(&tv, NULL);
	setting->starting_time = (tv.tv_sec * MILISECONDS) + (tv.tv_usec
			/ MILISECONDS);
	setting->forks = cutlery(setting);
	if (setting->forks == NULL)
		return (1);
	setting->philos = arrive(setting);
	if (setting->philos == NULL)
		return (1);
	setting->dead = false;
	setting->all_done = false;
	pthread_mutex_init(&setting->printing_m, NULL);
	pthread_mutex_init(&setting->all_done_m, NULL);
	pthread_mutex_init(&setting->dying_m, NULL);
	return (0);
}

static int	converting_parameters(t_dinner *setting, int argc, char **argv)
{
	setting->num_of = ft_atol(argv[1]);
	setting->time_to_die = ft_atol(argv[2]);
	setting->time_to_eat = ft_atol(argv[3]);
	setting->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
	{
		setting->rounds = ft_atol(argv[5]);
		if (setting->rounds <= 0)
			return (1);
	}
	else
		setting->rounds = -1;
	if (setting->num_of <= 0 || setting->time_to_die <= 0
		|| setting->time_to_eat <= 0 || setting->time_to_sleep <= 0)
		return (1);
	if (setting->num_of > INT_MAX || setting->time_to_die > INT_MAX
		|| setting->time_to_eat > INT_MAX || setting->time_to_sleep > INT_MAX
		|| setting->rounds > INT_MAX)
		return (1);
	return (0);
}

static t_forks	**cutlery(t_dinner *setting)
{
	t_forks	**forks;
	int		i;

	forks = malloc(setting->num_of * sizeof(t_forks *));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < setting->num_of)
	{
		forks[i] = malloc(sizeof(t_forks));
		if (!forks[i])
		{
			do_the_dishes(setting);
			return (NULL);
		}
		forks[i]->num = i + 1;
		forks[i]->in_use = false;
		pthread_mutex_init(&forks[i]->mutex, NULL);
		i++;
	}
	return (forks);
}

static t_philos	**arrive(t_dinner *setting)
{
	t_philos	**philos;
	int			i;

	philos = malloc(setting->num_of * sizeof(t_philos *));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < setting->num_of)
	{
		philos[i] = malloc(sizeof(t_philos));
		if (!philos[i])
		{
			say_goodbye(setting);
			return (NULL);
		}
		gather_around(philos[i], i, setting);
		i++;
	}
	return (philos);
}

static void	gather_around(t_philos *philos, int i, t_dinner *setting)
{
	philos->num = i + 1;
	philos->l_fork = setting->forks[i];
	if (setting->num_of != 1)
	{
		if (i == 0)
			philos->r_fork = setting->forks[setting->num_of - 1];
		else
			philos->r_fork = setting->forks[i - 1];
	}
	else
		philos->r_fork = NULL;
	philos->think = false;
	philos->sleep = true;
	philos->dead = false;
	philos->done = false;
	philos->rounds = setting->rounds;
	philos->last_meal = 0;
	philos->s = setting;
	pthread_mutex_init(&philos->last_meal_m, NULL);
	pthread_mutex_init(&philos->done_m, NULL);
}
