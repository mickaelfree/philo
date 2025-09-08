/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:56:47 by mickmart          #+#    #+#             */
/*   Updated: 2025/09/08 20:18:12 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	cleanup_threads(t_simu *simu, int count)
{
	while (--count >= 0)
		pthread_join(simu->philos[count].thread, NULL);
	return (1);
}

static int	cleanup_all_threads(t_simu *simu)
{
	int	i;

	simu->simulation_end = 1;
	i = 0;
	while (i < simu->nb_philo)
	{
		pthread_join(simu->philos[i].thread, NULL);
		i++;
	}
	return (1);
}

int	start_simulation(t_simu *simu)
{
	int			i;
	pthread_t	monitor;

	simu->start_time = get_time_ms();
	i = 0;
	while (i < simu->nb_philo)
	{
		if (pthread_create(&simu->philos[i].thread, NULL, philo_routine,
				&simu->philos[i]) != 0)
			return (cleanup_threads(simu, i));
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, simu) != 0)
		return (cleanup_all_threads(simu));
	i = 0;
	while (i < simu->nb_philo)
	{
		pthread_join(simu->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	return (0);
}
