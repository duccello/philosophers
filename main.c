/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
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

int	main(int argc, char **argv)
{
	t_dinner	*setting;

	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of arguments\n");
		return (1);
	}
	if (numeric_args(argv) == false)
	{
		printf("Non numeric cheeky arguments detected\n");
		return (1);
	}
	setting = malloc(sizeof(t_dinner));
	if (!setting)
		return (2);
	if (set_the_table(setting, argc, argv) == 0)
		mangia_ragazzi(setting);
	bye_bye(setting);
	return (0);
}
