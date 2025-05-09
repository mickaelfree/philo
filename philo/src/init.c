/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:54:13 by mickmart          #+#    #+#             */
/*   Updated: 2025/05/09 14:00:09 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_philos(t_simu *simu)
{
	int	i;

	i = 0;
	while (i < simu->nb_philo)
	{
		simu->philos[i].id = i + 1;
		simu->philos[i].meals_eaten = 0;
		simu->philos[i].last_meal = get_time_ms();
		simu->philos[i].left_fork = i;
		simu->philos[i].right_fork = (i + 1) % simu->nb_philo;
		simu->philos[i].simu = simu;
		pthread_mutex_init(&simu->philos[i].meal_mutex, NULL);
		i++;
	}
}

void	init_mutexes(t_simu *simu)
{
	int	i;

	i = 0;
	while (i < simu->nb_philo)
	{
		pthread_mutex_init(&simu->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&simu->print_mutex, NULL);
}
