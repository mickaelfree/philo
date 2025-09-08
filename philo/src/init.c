/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:54:13 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/04 02:37:36 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	cleanup_forks(t_simu *simu, int count)
{
	while (--count >= 0)
		pthread_mutex_destroy(&simu->forks[count]);
	free(simu->fork_status);
}

int	init_philos(t_simu *simu)
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
		if (pthread_mutex_init(&simu->philos[i].meal_mutex, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&simu->philos[i].meal_mutex);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_mutexes(t_simu *simu)
{
	int	i;

	simu->fork_status = malloc(sizeof(int) * simu->nb_philo);
	if (!simu->fork_status)
		return (0);
	i = 0;
	while (i < simu->nb_philo)
	{
		simu->fork_status[i] = 0;
		if (pthread_mutex_init(&simu->forks[i], NULL) != 0)
		{
			cleanup_forks(simu, i);
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(&simu->print_mutex, NULL) != 0)
	{
		cleanup_forks(simu, simu->nb_philo);
		return (0);
	}
	return (1);
}
