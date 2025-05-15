/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mickmart <mickmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:11:16 by mickmart          #+#    #+#             */
/*   Updated: 2025/05/13 23:50:42 by mickmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*monitor_routine(void *arg)
{
	t_simu	*simu;
	int		i;
	int		all_ate_enough;

	simu = (t_simu *)arg;
	while (!simu->simulation_end)
	{
		i = 0;
		all_ate_enough = 1;
		while (i < simu->nb_philo)
		{
			pthread_mutex_lock(&simu->philos[i].meal_mutex);
                        if (get_time_ms() - simu->philos[i].last_meal > simu->time_to_die)
			{
				pthread_mutex_unlock(&simu->philos[i].meal_mutex);
				print_action(simu, simu->philos[i].id, DIE);
				pthread_mutex_lock(&simu->print_mutex);
				simu->simulation_end = 1;
				pthread_mutex_unlock(&simu->print_mutex);
				return (NULL);
			}
			if (simu->nb_eat > 0 && simu->philos[i].meals_eaten < simu->nb_eat)
				all_ate_enough = 0;
			pthread_mutex_unlock(&simu->philos[i].meal_mutex);
			i++;
		}
		if (simu->nb_eat > 0 && all_ate_enough)
		{
			pthread_mutex_lock(&simu->print_mutex);
			simu->simulation_end = 1;
			pthread_mutex_unlock(&simu->print_mutex);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
