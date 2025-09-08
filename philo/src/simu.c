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
		{
			printf("Error: Failed to create philosopher thread %d\n", i + 1);
			while (--i >= 0)
				pthread_join(simu->philos[i].thread, NULL);
			return (1);
		}
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, simu) != 0)
	{
		printf("Error: Failed to create monitor thread\n");
		simu->simulation_end = 1;
		i = 0;
		while (i < simu->nb_philo)
		{
			pthread_join(simu->philos[i].thread, NULL);
			i++;
		}
		return (1);
	}
	i = 0;
	while (i < simu->nb_philo)
	{
		if (pthread_join(simu->philos[i].thread, NULL) != 0)
		{
			printf("Error: Failed to join philosopher thread %d\n", i + 1);
			return (1);
		}
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
	{
		printf("Error: Failed to join monitor thread\n");
		return (1);
	}
	return (0);
}
