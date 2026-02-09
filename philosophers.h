/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duccello <duccello@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:18:17 by duccello          #+#    #+#             */
/*   Updated: 2025/10/13 18:26:58 by duccello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define MILISECONDS 1000
# define VIP_GUEST 2

# include <pthread.h>
# include <stdbool.h>

typedef struct s_dinner	t_dinner;

typedef struct s_forks
{
	int					num;
	bool				in_use;
	pthread_mutex_t		mutex;
}						t_forks;

typedef struct s_philos
{
	int					num;
	long				current_time;
	t_forks				*r_fork;
	t_forks				*l_fork;
	bool				think;
	bool				sleep;
	bool				dead;
	bool				done;
	int					rounds;
	long				last_meal;
	pthread_t			thread;
	pthread_mutex_t		last_meal_m;
	pthread_mutex_t		done_m;
	t_dinner			*s;
}						t_philos;

typedef struct s_dinner
{
	long				starting_time;
	long				num_of;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				rounds;
	bool				dead;
	bool				all_done;
	t_philos			**philos;
	t_forks				**forks;
	pthread_mutex_t		printing_m;
	pthread_mutex_t		dying_m;
	pthread_mutex_t		all_done_m;
}						t_dinner;

int						set_the_table(t_dinner *setting, int argc, char **argv);
int						serve(t_dinner *setting);
void					*mangia_ragazzi(t_dinner *setting);
void					*bon_apetit(void *philos);
void					say_goodbye(t_dinner *settings);
void					do_the_dishes(t_dinner *settings);
void					clean_the_table(t_dinner *settings);
void					bye_bye(t_dinner *settings);
long					timestamp(t_philos *philos);
bool					numeric_args(char **argv);
long					ft_atol(const char *p);
bool					check(t_dinner *setting);
void					drop_them_forks(t_philos *philos);
bool					take_forks(t_philos *philos, t_forks *first,
							t_forks *second);
bool					eating(t_philos *philos);
bool					sleeping(t_philos *philos);
bool					thinking(t_philos *philos);
void					*time_to_die(void *arg);
bool					done(t_dinner *setting);
bool					dead(t_dinner *setting);

#endif
